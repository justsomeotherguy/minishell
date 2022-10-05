/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:10:33 by jwilliam          #+#    #+#             */
/*   Updated: 2022/10/05 12:31:30 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

void	init_super(void)
{
	g_super.envar = (t_envar *)malloc(sizeof(t_envar));
	g_super.envar = NULL;
	g_super.builtins = malloc(sizeof(char **) * (8 + 34));
	g_super.builtins = set_builtin(g_super.builtins);
}
