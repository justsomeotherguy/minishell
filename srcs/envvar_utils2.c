/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:49:09 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/06 13:49:40 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

void	do_remove_envar(t_envar *to_remove, t_envar *prev)
{
	if (!prev)
	{
		g_super.envar = to_remove->next;
		free_envar(to_remove);
	}
	else
	{
		prev->next = to_remove->next;
		free_envar(to_remove);
	}
	return ;
}
