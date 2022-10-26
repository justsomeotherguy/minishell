/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:38:05 by jwilliam          #+#    #+#             */
/*   Updated: 2022/10/26 15:13:07 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_super		g_super;

static void	print_cmds(void)
{
	t_cmdset	*temp;
	int			i;
	int			j;

	temp = g_super.cmds;
	i = 0;
	j = 0;
	while (temp)
	{
		while (temp->tokens[j])
		{
			printf("cmd set %i, token %s\n", i, temp->tokens[j]);
			j++;
		}
		temp = temp->next;
		j = 0;
		i++;
	}
}

static char	*get_prompt(void)
{
	char	*prompt;
	t_envar	*temp;

	prompt = ft_strdup(T_RED);
	temp = find_env(g_super.envar, "USER");
	if (temp)
	{
		prompt = ft_strjoin(prompt, (char *)temp->data);
		prompt = ft_strjoin(prompt, "@minishell ");
	}	
	else
	{
		prompt = ft_strjoin(prompt, "guest");
		prompt = ft_strjoin(prompt, "@minishell ");
	}
	temp = find_env(g_super.envar, "PWD");
	prompt = ft_strjoin(prompt, T_BLUE);
	if (temp)
		prompt = ft_strjoin(prompt, (char *)temp->data);
	else
		prompt = ft_strjoin(prompt, "Unable to find $PWD");
	prompt = ft_strjoin(prompt, T_DEFAULT);
	prompt = ft_strjoin(prompt, " $> ");
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	init_super();
	set_env(envp);
	while (1)
	{
//		signal(SIGINT, sig_handler_int);
//		signal(SIGQUIT, SIG_IGN);
		line = readline(get_prompt());
		if (!line)
			printf("Empty line");
		else
		{
			add_history(line);
			g_super.full_tokens = make_tokens(line);
			parse_token();
			print_cmds();
			executor();
		}
		free_cmds(&g_super.cmds);
		free_2d_array(g_super.full_tokens);
		free(line);
	}
//	rl_clear_history();
	return (0);
}
