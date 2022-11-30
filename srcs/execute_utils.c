/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:48:45 by jwilliam          #+#    #+#             */
/*   Updated: 2022/11/30 14:30:10 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

int	ft_dup2(int old, int new)
{
	if (dup2(old, new) < 0)
		return (-1);
	close(old);
	return (0);
}

void	set_fds(void)
{
	t_cmdset		*to_set;
	int				i;

	to_set = g_super.cmds;
	i = 0;
	while (to_set != NULL)
	{
		set_fd_in(to_set);
		dprintf(2, "cmd set %i - fd in %i\n", i, to_set->fd_in);
		set_fd_out(to_set);
		dprintf(2, "cmd set %i - fd out %i\n", i, to_set->fd_out);
		i++;
		to_set = to_set->next;
	}
	return ;
}
