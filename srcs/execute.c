/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:36:29 by jwilliam          #+#    #+#             */
/*   Updated: 2022/11/29 16:53:37 by jwilliam         ###   ########.fr       */
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

void	open_close(t_cmdset *current, int *curr_p, int *next_p)
{
	if (current->cmd_no != 0)
	{
		dprintf(2, "close read end\n");
		close(curr_p[1]);
		ft_dup2(curr_p[0], STDIN_FILENO);
	}
	if (current->next != NULL)
	{
		dprintf(2, "close write end\n");
		close(next_p[0]);
		ft_dup2(next_p[1], STDOUT_FILENO);
	}
}

int	set_redir(t_cmdset *current, int *curr_p)
{
	if (current->fd_in != 0)
	{
		if (ft_dup2(current->fd_in, STDIN_FILENO < 0))
			return (-1); // to do error
	}
	if (current->fd_out != 1)
	{
		if (ft_dup2(current->fd_out, STDOUT_FILENO < 0))
			return (-1); // to do error
	}
	else if (current->next && dup2(curr_p[1], STDOUT_FILENO) < 0)
		return (-1); // to do error
	close(curr_p[1]);
	return (0);
}

int	pipe_exec(t_cmdset *current, int *curr_p, int *next_p)
{
	set_redir(current, curr_p);
	close(curr_p[0]);
	if (is_builtin(current->tokens) >= 0)
	{
		dprintf(2, "do builtin\n");
		do_builtin(is_builtin(current->tokens), current->tokens);
	}
	else
	{
		dprintf(2, "fork process\n");
		g_super.pid = fork();
		dprintf(2, "created fork - %i\n", g_super.pid);
		if (g_super.pid < 0)
			return (-1); // to do error
		if (g_super.pid == 0)
		{
			dprintf(2, "child process\n");
			open_close(current, curr_p, next_p);
			exec_cmd(current->tokens);
		}
	}
	dprintf(2, "end pipe exec\n");
	return (0);
}


void	pipe_exec_fin(t_cmdset *current, int *curr_p, int *next_p)
{
	if (g_super.pid > 0)
	{
		dprintf(2, "parent process\n");
		if (current->cmd_no != 0)
		{
			dprintf(2, "close old pipes\n");
			close(curr_p[0]);
			close(curr_p[1]);
		}
		if (current->next != NULL)
		{
			dprintf(2, "set to new pipes\n");
			curr_p[0] = next_p[0];
			curr_p[1] = next_p[1];
		}
	}
	waitpid(g_super.pid, &g_super.status, 0);
}

int	set_pipe(t_cmdset *current, int *next_p)
{
	if (current->next != NULL)
	{
		dprintf(2, "cmd set %i - create pipe\n", current->cmd_no);
		if (pipe(next_p) < 0)
			return (-1); // to do error
	}
	return (0);
}

void	executor(void)
{
	t_cmdset	*current;
	int			curr_p[2];
	int			next_p[2];

	current = g_super.cmds;
	set_fds();
	while (current != NULL)
	{
//		dprintf(2, "cmd no - %i\n", current->cmd_no);
		if (set_pipe(current, next_p) != 0)
			return ; // to do error
//		dprintf(2, "pid - %i\n", g_super.pid);
		pipe_exec(current, curr_p, next_p);
		pipe_exec_fin(current, curr_p, next_p);
//		dprintf(2, "after child pid - %i\n", g_super.pid);
		current = current->next;
	}
	return ;
}
