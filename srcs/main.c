/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:38:05 by jwilliam          #+#    #+#             */
/*   Updated: 2022/10/07 15:07:12 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_super		g_super;

int	main(int argc, char **argv, char **envp)
{
	t_super	g_super;
	char	*line;
	char	**tokens;

	init_super();
	set_env(envp);
	print_env();
	signal(SIGQUIT, sig_handler_quit);
	while (1)
	{
		signal(SIGINT, sig_handler_int);
		line = readline("Super Cool Line: ");
		if (!line)
			printf("Empty line");
		else
		{
			add_history(line);
			printf("\"%s\" was written in line\n", line);
			tokens = make_tokens(line);
			is_builtin(tokens);
		}
		free(line);
	}
//	rl_clear_history();
	return (0);
}
