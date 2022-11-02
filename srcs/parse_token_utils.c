/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:05:16 by jwilliam          #+#    #+#             */
/*   Updated: 2022/11/02 14:29:32 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

t_cmdset	*new_cmdset(void)
{
	t_cmdset	*new;

	new = (t_cmdset *)malloc(sizeof(t_cmdset));
	if (!new)
		return (NULL);
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->tokens = NULL;
	new->next = NULL;
	return (new);
}

/*

*/
void	add_cmdset(t_cmdset **cmdset, t_cmdset *new)
{
	t_cmdset	*add;

	if (!new)
		return ;
	if (!*cmdset)
		*cmdset = new;
	else
	{
		add = to_last_cmdset(*cmdset);
		add->next = new;
	}
}

/*
Gets the last node entry in the environment variables list.
*/
t_cmdset	*to_last_cmdset(t_cmdset *cmdset)
{
	if (!cmdset)
		return (NULL);
	while (cmdset)
	{
		if (!cmdset->next)
			return (cmdset);
		cmdset = cmdset->next;
	}
	return (cmdset);
}
