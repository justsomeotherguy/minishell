/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:39:25 by jwilliam          #+#    #+#             */
/*   Updated: 2022/09/21 15:31:20 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "teststuff.h"

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
	char	**builtin;
	int		i;
	int		j;

	i = 0;
	j = 0;
	builtin = malloc(sizeof(char **) * (8 + 34));
	builtin = set_builtin(builtin);
	while (tokens[i])
	{
		while (builtin[j])
		{
			if (ft_strcmp(tokens[i], builtin[j]) == 0)
			{
				printf("line has %s\n", builtin[j]);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return ;
}
