/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:48:45 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/02 16:18:14 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

/* 

Doesn't work as well as I had hoped

int	ft_dup2(int old, int new)
{
	if (dup2(old, new) < 0)
		return (-1);
	close(old);
	return (0);
}
*/

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

int	set_redir(t_cmdset *current)
{
	dprintf(2, "set redirect\n");
	set_fd_in(current);
	if (current->fd_in > 2)
	{
		dprintf(2, "child - close file in\n");
		if (dup2(current->fd_in, STDIN_FILENO) < 0)
			return (-1); // to do error
		close(current->fd_in);
	}
	set_fd_out(current);
	if (current->fd_out > 2)
	{
		dprintf(2, "child - close file out\n");
		if (dup2(current->fd_out, STDOUT_FILENO) < 0)
			return (-1); // to do error
		close(current->fd_out);
	}
	return (0);
}

void	open_close(t_cmdset *current, int *old_p, int *new_p)
{
	dprintf(2, "check to open and close\n");
	if (current->cmd_no != 0)
	{
		dprintf(2, "child - close inbetween pipes\n");
		close(old_p[1]);
		dprintf(2, "child - close curr_p[1]\n");
		if (dup2(old_p[0], STDIN_FILENO) < 0)
			return ; // to do error
		close(old_p[0]);
		dprintf(2, "child - dup and close curr_p[0] to stdin\n");
	}
	if (current->next != NULL)
	{
		dprintf(2, "child - close last pipe\n");
		close(new_p[0]);
		dprintf(2, "child - close next_p[0]\n");
		if (dup2(new_p[1], STDOUT_FILENO) < 0)
			return ; // to do error
		close(new_p[1]);
		dprintf(2, "child - dup and close next_p[1] to stdout\n");
	}
}
