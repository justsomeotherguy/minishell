/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:39:25 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/02 15:08:55 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

/*
Check input tokens to verify if they match any of the builtin commands,
if one is found, set builtin id int and pass to switcher function.
*/
int	is_builtin_child(char **tokens)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tokens[i] && i == 0)
	{
		while (g_super.builtins[j])
		{
			if (j == 0 || j == 2 || j == 5)
			{
				if (ft_strcmp(tokens[i], g_super.builtins[j]) == 0)
					return (j);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (-1);
}

/*
Check input tokens to verify if they match any of the builtin commands,
if one is found, set builtin id int and pass to switcher function.
*/
int	is_builtin_parent(char **tokens)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tokens[i] && i == 0)
	{
		while (g_super.builtins[j])
		{
			if (j == 1 || j == 3 || j == 4 || j == 6)
			{
				if (ft_strcmp(tokens[i], g_super.builtins[j]) == 0)
					return (j);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (-1);
}

/*
Switcher to check what builtin was used and pass tokens to the appropriate
builtin commands function.

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
	if (builtin_id == 1)
		builtin_cd(tokens);
	if (builtin_id == 2)
		builtin_pwd();
	if (builtin_id == 3)
		builtin_export(tokens);
	if (builtin_id == 4)
		find_and_remove(g_super.envar, tokens[1]);
	if (builtin_id == 5)
		print_env();
	if (builtin_id == 6)
		exit(0);
}
