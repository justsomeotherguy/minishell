/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:38:05 by jwilliam          #+#    #+#             */
/*   Updated: 2022/10/13 14:26:24 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_super		g_super;

static char	*get_prompt(void)
{
	char	*prompt;
	t_envar	*temp;

	temp = find_env(g_super.envar, "USER");
	if (temp)
		prompt = ft_strjoin((char *)temp->data, "@minishell ");
	else
		prompt = ft_strjoin("guest", "@minishell ");
	temp = find_env(g_super.envar, "PWD");
	if (temp)
		prompt = ft_strjoin(prompt, (char *)temp->data);
	else
		prompt = ft_strjoin(prompt, "Unable to find $PWD");
	prompt = ft_strjoin(prompt, " >$ ");
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_super	g_super;
	char	*line;
	char	**tokens;

	init_super();
	set_env(envp);
	signal(SIGQUIT, sig_handler_quit);
	while (1)
	{
		signal(SIGINT, sig_handler_int);
		line = readline(get_prompt());
		if (!line)
			printf("Empty line");
		else
		{
			add_history(line);
			tokens = make_tokens(line);
			if (is_builtin(tokens) < 0)
				executor(tokens);
		}
		free(line);
	}
//	rl_clear_history();
	return (0);
}
