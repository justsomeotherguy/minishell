/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:38:05 by jwilliam          #+#    #+#             */
/*   Updated: 2022/09/21 15:12:52 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "teststuff.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**tokens;
	int		i;

	argc = 0;
	argv = 0;
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	signal(SIGINT, sig_handler_int);
	signal(SIGQUIT, sig_handler_quit);
	while (1)
	{
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
	return (0);
}
