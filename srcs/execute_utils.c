/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:48:45 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/02 15:39:29 by jwilliam         ###   ########.fr       */
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
		set_fd_out(to_set);
		i++;
		to_set = to_set->next;
	}
	return ;
}

int	set_redir(t_cmdset *current)
{
	set_fd_in(current);
	if (current->fd_in > 2)
	{
		if (dup2(current->fd_in, STDIN_FILENO) < 0)
			return (-1); // to do error
		close(current->fd_in);
	}
	set_fd_out(current);
	if (current->fd_out > 2)
	{
		if (dup2(current->fd_out, STDOUT_FILENO) < 0)
			return (-1); // to do error
		close(current->fd_out);
	}
	return (0);
}

void	open_close(t_cmdset *current, int *old_p, int *new_p)
{
	if (current->cmd_no != 0)
	{
		close(old_p[1]);
		if (dup2(old_p[0], STDIN_FILENO) < 0)
			return ; // to do error
		close(old_p[0]);
	}
	if (current->next != NULL)
	{
		close(new_p[0]);
		if (dup2(new_p[1], STDOUT_FILENO) < 0)
			return ; // to do error
		close(new_p[1]);
	}
}
