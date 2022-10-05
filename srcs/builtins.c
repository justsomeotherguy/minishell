/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:39:25 by jwilliam          #+#    #+#             */
/*   Updated: 2022/10/05 12:32:54 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_super	g_super;

char	**set_builtin(char **builtin)
{
	builtin[0] = "echo";
	builtin[1] = "cd";
	builtin[2] = "pwd";
	builtin[3] = "export";
	builtin[4] = "unset";
	builtin[5] = "env";
	builtin[6] = "exit";
	builtin[7] = 0;
	return (builtin);
}

void	is_builtin(char **tokens)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		while (g_super.builtins[j])
		{
			if (ft_strcmp(tokens[i], g_super.builtins[j]) == 0)
			{
				printf("line has %s\n", g_super.builtins[j]);
				do_builtin(j);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return ;
}

void	do_builtin(int builtin_id)
{
	if (builtin_id == 5)
		print_env();
	if (builtin_id == 6)
		exit(0);
}
