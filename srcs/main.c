/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:38:05 by jwilliam          #+#    #+#             */
/*   Updated: 2022/10/19 16:07:20 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_super		g_super;

static void	print_cmds(void)
{
	for (int i = 0; g_super.cmds; i++)
	{
		printf("cmd set %i\n", i);
		int	j = 0;
		while (g_super.cmds[i].tokens[j])
		{
			printf("%s\n", g_super.cmds[i].tokens[j]);
			j++;
		}
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
		signal(SIGINT, sig_handler_int);
		signal(SIGQUIT, SIG_IGN);
		line = readline(get_prompt());
		if (!line)
			printf("Empty line");
		else
		{
			add_history(line);
			g_super.full_tokens = make_tokens(line);
			parse_token();
			print_cmds();
			if (is_builtin(g_super.full_tokens) < 0)
				executor(g_super.full_tokens);
		}
		free(line);
	}
//	rl_clear_history();
	return (0);
}
