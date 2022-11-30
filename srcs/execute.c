/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:36:29 by jwilliam          #+#    #+#             */
/*   Updated: 2022/11/30 16:15:56 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

void	exec_cmd(char **cmds)
{
	char	**paths;
	char	*exec_path;

	paths = init_pathlist();
	if (!paths)
		exit(1); // to_do error
	exec_path = get_path_for_cmd(paths, cmds[0]);
	if (!exec_path)
		exit(1); // to_do error
	if (execve(exec_path, cmds, g_super.envar_arr) == -1)
	{
		ft_putstr_fd("Unable to execute command\n", 2);
		exit(1); // to_do error
	}
	exit(0);
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
//		ft_dup2(old_p[0], STDIN_FILENO);
		dprintf(2, "child - dup and close curr_p[0] to stdin\n");
	}
	if (current->next != NULL)
	{
		dprintf(2, "child - close last pipe\n");
		close(new_p[0]);
		dprintf(2, "child - close next_p[0]\n");
//		ft_dup2(new_p[1], STDOUT_FILENO);
		if (dup2(new_p[1], STDOUT_FILENO) < 0)
			return ; // to do error
		close(new_p[1]);
		dprintf(2, "child - dup and close next_p[1] to stdout\n");
	}
}

int	set_redir(t_cmdset *current)
{
	dprintf(2, "set redirect\n");
	set_fd_in(current);
	if (current->fd_in != 0)
	{
		if (dup2(current->fd_out, STDOUT_FILENO) < 0)
			return (-1); // to do error
		close(current->fd_out);
//		if (ft_dup2(current->fd_in, STDIN_FILENO < 0))
//			return (-1); // to do error
		dprintf(2, "child - close file in\n");
	}
	set_fd_out(current);
	if (current->fd_out != 1)
	{
		if (dup2(current->fd_out, STDOUT_FILENO) < 0)
			return (-1); // to do error
		close(current->fd_out);
//		if (ft_dup2(current->fd_out, STDOUT_FILENO < 0))
//			return (-1); // to do error
		dprintf(2, "child - close file out\n");
	}
//	else if (current->next && dup2(curr_p[1], STDOUT_FILENO) < 0)
//		return (-1); // to do error
//	close(curr_p[1]);
	return (0);
}

int	pipe_exec(t_cmdset *current, int *curr_p, int *new_p)
{
	dprintf(2, "child process\n");
	open_close(current, curr_p, new_p);
	set_redir(current);
	if (is_builtin(current->tokens) >= 0)
		do_builtin(is_builtin(current->tokens), current->tokens);
	else
		exec_cmd(current->tokens);
	return (0);
}


void	pipe_exec_fin(t_cmdset *current, int *old_p, int *new_p)
{
	dprintf(2, "parent process\n");
	if (current->cmd_no != 0)
	{
		close(old_p[0]);
		dprintf(2, "parent - old_p[0] pipe closed\n");
		close(old_p[1]);
		dprintf(2, "parent - old_p[1] pipe closed\n");
	}
	if (current->next != NULL)
	{
		old_p[0] = new_p[0];
		dprintf(2, "parent - old_p[0] to new_p[0]\n");
		old_p[1] = new_p[1];
		dprintf(2, "parent - old_p[1] to new_p[1]\n");
	}
	waitpid(g_super.pid, &g_super.status, 0);
}

int	set_pipe(t_cmdset *current, int *new_p)
{
	if (current->next != NULL)
	{
		dprintf(2, "cmd set %i - create pipe\n", current->cmd_no);
		if (pipe(new_p) < 0)
			return (-1); // to do error
	}
	g_super.pid = fork();
	if (g_super.pid < 0)
		return (-1); // to do error
	return (0);
}

void	executor(void)
{
	t_cmdset	*current;
	int			old_p[2];
	int			new_p[2];

	current = g_super.cmds;
//	set_fds();
	while (current != NULL)
	{
//		dprintf(2, "cmd no - %i\n", current->cmd_no);
		if (set_pipe(current, new_p) != 0)
			return ; // to do error
//		dprintf(2, "pid - %i\n", g_super.pid);
		if (g_super.pid == 0)
			pipe_exec(current, old_p, new_p);
		else if (g_super.pid > 0)
			pipe_exec_fin(current, old_p, new_p);
		else
			return ; // to do error
//		dprintf(2, "after child pid - %i\n", g_super.pid);
		current = current->next;
	}
	return ;
}
