/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:36:29 by jwilliam          #+#    #+#             */
/*   Updated: 2022/11/28 18:10:42 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

void	exec_cmd(char **cmds)
{
	char	**paths;
	char	*exec_path;

	dprintf(2, "exec cmd\n");
	paths = init_pathlist();
	if (!paths)
		exit(1); // to_do error
	exec_path = get_path_for_cmd(paths, cmds[0]);
	if (!exec_path)
		exit(1); // to_do error
	if (execve(exec_path, cmds, g_super.envar_arr) == -1)
	{
		printf("Unable to execute command\n");
		exit(1); // to_do error
	}
	exit(0);
}

void	open_close(t_cmdset *current, int *left, int *right)
{
	if (current->cmd_no != 0)
	{
		dprintf(2, "close read end\n");
		close(left[1]);
		ft_dup2(left[0], STDIN_FILENO);
	}
	if (current->next != NULL)
	{
		dprintf(2, "close write end\n");
		close(right[0]);
		ft_dup2(right[1], STDOUT_FILENO);
	}
}

int	pipe_exec(t_cmdset *current, int *left, int *right)
{
	if (g_super.pid == 0)
	{
		dprintf(2, "child process\n");
		open_close(current, left, right);
		if (is_builtin(current->tokens) >= 0)
		{
			do_builtin(is_builtin(current->tokens), current->tokens);
			return (0);
		}
		else
			exec_cmd(current->tokens);
	}
	return (0);
}

void	pipe_exec_fin(t_cmdset *current, int *left, int *right)
{
	if (g_super.pid > 0)
	{
		dprintf(2, "parent process\n");
		if (current->cmd_no != 0)
		{
			dprintf(2, "close old pipes\n");
			close(left[0]);
			close(left[1]);
		}
		if (current->next != NULL)
		{
			dprintf(2, "set to new pipes\n");
			left[0] = right[0];
			left[1] = right[1];
		}
	}
	waitpid(g_super.pid, &g_super.status, 0);
}

int	set_pipe(t_cmdset *current, int *right, int pid)
{
	if (current->next)
	{
		dprintf(2, "create pipe\n");
		if (pipe(right) < 0)
			return (-1); // to do error
	}
	dprintf(2, "fork process\n");
	g_super.pid = fork();
	dprintf(2, "created fork - %i\n", g_super.pid);
	if (g_super.pid < 0)
	{
		return (-1); // to do error
	}
	return (0);
}

void	executor(void)
{
	t_cmdset	*current;
	int			left[2];
	int			right[2];

	current = g_super.cmds;
	set_fds();
	while (current != NULL)
	{
		dprintf(2, "cmd no - %i\n", current->cmd_no);
		if (set_pipe(current, right, g_super.pid) != 0)
			return ; // to do error
		dprintf(2, "pid - %i\n", g_super.pid);
		pipe_exec(current, left, right);
		pipe_exec_fin(current, left, right);
		dprintf(2, "after child pid - %i\n", g_super.pid);
		current = current->next;
	}
	return ;
}
