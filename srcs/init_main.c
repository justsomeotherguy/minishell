/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:10:33 by jwilliam          #+#    #+#             */
/*   Updated: 2022/10/19 14:15:19 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

/*
Initialize global variable super.
Allocate memory for environment variables and preset builtin command strings.
*/
void	init_super(void)
{
	g_super.envar = (t_envar *)malloc(sizeof(t_envar));
	g_super.envar = NULL;
	g_super.builtins = malloc(sizeof(char **) * 8);
	g_super.builtins = set_builtin(g_super.builtins);
}

/*
Generate preset builtin commands character strings
*/
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
