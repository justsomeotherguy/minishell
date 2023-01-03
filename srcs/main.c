/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:38:05 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/03 21:05:09 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_super		g_super;

static void	free_main_items(char *line, char *prompt)
{
	if (g_super.cmds)
		free_cmds(&g_super.cmds);
	if (g_super.full_tokens)
		free_2d_array(g_super.full_tokens);
	if (line)
		free(line);
	if (prompt)
		free(prompt);
}

static char	*get_prompt(void)
{
	char	*prompt;
	t_envar	*temp;

	prompt = ft_strdup(T_RED);
	temp = find_env(g_super.envar, "USER");
	if (temp)
	{
		prompt = ft_strjoin_safe_free(prompt, (char *)temp->data, true, false);
		prompt = ft_strjoin_safe_free(prompt, "@minishell ", true, false);
	}	
	else
	{
		prompt = ft_strjoin_safe_free(prompt, "guest", true, false);
		prompt = ft_strjoin_safe_free(prompt, "@minishell ", true, false);
	}
	temp = find_env(g_super.envar, "PWD");
	prompt = ft_strjoin_safe_free(prompt, T_BLUE, true, false);
	if (temp)
		prompt = ft_strjoin_safe_free(prompt, (char *)temp->data, true, false);
	else
		prompt = ft_strjoin_safe_free(prompt, "Unable to find $PWD", true,
				false);
	prompt = ft_strjoin_safe_free(prompt, T_DEFAULT, true, false);
	prompt = ft_strjoin_safe_free(prompt, " $> ", true, false);
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*prompt;

	init_super();
	set_env(argc, argv, envp);
	rebuild_envar_arr();
	make_signal();
	while (1)
	{
		prompt = get_prompt();
		if (prompt == NULL)
			return (1);
		line = readline(prompt);
		if (!line)
			break ;
		else
		{
			add_history(line);
			g_super.full_tokens = make_tokens(line);
			parse_token();
			executor();
		}
		free_main_items(line, prompt);
	}
	exit(g_super.status);
}
