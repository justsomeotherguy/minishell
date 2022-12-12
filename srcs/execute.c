/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:36:29 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/12 20:53:02 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

void	exec_cmd(char **cmds)
{
	char	**paths;
	char	*exec_path;

	if (cmds[0][0] == '/')
	{
		if (execve(cmds[0], cmds, g_super.envar_arr) == -1)
		{
			error_message("command not found", 127);
			exit(127);
		}
	}
	paths = init_pathlist();
	if (!paths)
	{
		error_message("command not found", 127);
		exit(127);
	}
	exec_path = get_path_for_cmd(paths, cmds[0]);
	if (!exec_path)
	{
		error_message("command not found", 127);
		exit(127);
	}
	if (execve(exec_path, cmds, g_super.envar_arr) == -1)
	{
		error_message("command not found", 127);
		exit(127);
	}
}

int	pipe_exec(t_cmdset *current, int *curr_p, int *new_p)
{
	make_signal();
//	dprintf(2, "child process\n");
	open_close(current, curr_p, new_p);
	set_redir(current);
	if (is_builtin_child(current->tokens) >= 0)
		do_builtin(is_builtin_child(current->tokens), current->tokens);
	else
		exec_cmd(current->tokens);
	exit(0);
}

void	pipe_exec_fin(t_cmdset *current, int *old_p, int *new_p)
{
	int		status;

//	dprintf(2, "parent process\n");
	if (current->cmd_no != 0)
	{
		close(old_p[0]);
//		dprintf(2, "parent - old_p[0] pipe closed\n");
		close(old_p[1]);
//		dprintf(2, "parent - old_p[1] pipe closed\n");
	}
	if (current->next != NULL)
	{
		old_p[0] = new_p[0];
//		dprintf(2, "parent - old_p[0] to new_p[0]\n");
		old_p[1] = new_p[1];
//		dprintf(2, "parent - old_p[1] to new_p[1]\n");
	}
	waitpid(g_super.pid, &status, 0);
	if (WIFEXITED(status))
		g_super.status = WEXITSTATUS(status);
}

int	set_pipe(t_cmdset *current, int *new_p)
{
	if (current->next != NULL)
	{
//		dprintf(2, "cmd set %i - create pipe\n", current->cmd_no);
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
	if (is_builtin_parent(current->tokens) >= 0 && current->next == NULL)
	{
		do_builtin(is_builtin_parent(current->tokens), current->tokens);
		return ;
	}
	while (current != NULL)
	{
		if (set_pipe(current, new_p) != 0)
			return ; // to do error
		if (g_super.pid == 0)
			pipe_exec(current, old_p, new_p);
		else if (g_super.pid > 0)
			pipe_exec_fin(current, old_p, new_p);
		else
			return ; // to do error
		current = current->next;
	}
	return ;
}
