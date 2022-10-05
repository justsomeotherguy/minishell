/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:39:25 by jwilliam          #+#    #+#             */
/*   Updated: 2022/10/05 16:14:23 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_super	g_super;

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
				do_builtin(j, tokens);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return ;
}

/*
Builtin IDs
0 = echo;
1 = cd;
2 = pwd;
3 = export;
4 = unset;
5 = env;
6 = exit;
*/
void	do_builtin(int builtin_id, char **tokens)
{
	if (builtin_id == 0)
		builtin_echo(tokens);
	if (builtin_id == 3)
		builtin_export(tokens);
	if (builtin_id == 4)
		find_and_remove(g_super.envar, tokens[1]);
	if (builtin_id == 5)
		print_env();
	if (builtin_id == 6)
		exit(0);
}

void	builtin_export(char **tokens)
{
	char		**split;
	int			i;

	split = ft_split(tokens[1], '=');
	i = 0;
	if (!split[1])
		return ;
	else
	{
		add_env(&g_super.envar, new_env(split[0], split[1]));
	}
	free(split);
}

void	builtin_echo(char **tokens)
{
	int			i;
	int			option;

	i = 1;
	option = 0;
	if (ft_strcmp(tokens[1], "-n") == 0)
	{
		i++;
		option++;
	}
	while (tokens[i])
	{	
		printf("%s", tokens[i]);
		i++;
		if (tokens[i] != 0)
			printf(" ");
	}
	if (option != 1)
		printf("\n");
}
