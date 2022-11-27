/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:36:29 by jwilliam          #+#    #+#             */
/*   Updated: 2022/11/28 00:33:47 by jwilliam         ###   ########.fr       */
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

static void	open_close(t_cmdset *current, int *left, int *right)
{
	if (current->cmd_no != 0)
	{
		close(left[1]);
		ft_dup2(left[0], STDIN_FILENO);
	}
	if (current->next)
	{
		close(right[0]);
		ft_dup2(right[1], STDOUT_FILENO);
	}
}

static void	pipe_exec(t_cmdset *current, int *left, int *right)
{
	if (current->pid == 0)
	{
		open_close(current, left, right);
		if (is_builtin(current->tokens) >= 0)
			do_builtin(is_builtin(current->tokens), current->tokens);
		else
			exec_cmd(current->tokens);
	}
	exit(0);
}

static void	pipe_exec_fin(t_cmdset *current, int *left, int *right)
{
	if (current->pid != 0)
	{
		if (current->cmd_no != 0)
		{
			close(left[0]);
			close(left[1]);
		}
		if (current->next)
		{
			left[0] = right[0];
			left[1] = right[1];
		}
		waitpid(current->pid, &g_super.status, 0);
	}
}

void	exec_single(t_cmdset *current)
{
	if (current->fd_in != 0)
	{
		dup2(current->fd_in, STDIN_FILENO);
		close(current->fd_in);
	}
	if (current->fd_out != 1)
	{
		dup2(current->fd_out, STDOUT_FILENO);
		close(current->fd_out);
	}
	if (is_builtin(current->tokens) >= 0)
		do_builtin(is_builtin(current->tokens), current->tokens);
	else
	{
		current->pid = fork();
		if (current->pid == 0)
			exec_cmd(current->tokens);
		waitpid(current->pid, &g_super.status, 0);
	}
	return ;
}


static int	set_pipe(t_cmdset *current, int *right)
{
	if (current->next)
	{
		if (pipe(right) < 0)
			return (-1); // to do error
	}
	current->pid = fork();
	if (current->pid < 0)
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
	if (!current->next)
		exec_single(current);
	else
	{
		while (current)
		{
			if (set_pipe(current, right) == 0)
				return ; // to do error
			pipe_exec(current, left, right);
			pipe_exec_fin(current, left, right);
			current = current->next;
		}
	}
	return ;
}

/*
void	executor(void)
{
	t_cmdset	*current;
	t_cmdset	*prev;

	current = g_super.cmds;
	prev = NULL;
	set_fds();
	if (!current->next)
		exec_single(current);
	else
	{
		int i = 0;
		while (current)
		{
			i++;
			dprintf(2, "Pipeline: %d\n", i);

			if (current->next)
				pipe(current->pipefd); // to_do error
			set_and_dup(current, prev); // to_do error
			current->pid = fork(); // to_do error			
			if (current->pid == 0)
				pipe_exec(current);
			if (current->next)
			{
				ft_dup2(current->pipefd[0], STDIN_FILENO);
				close(current->pipefd[1]);
			}	
			waitpid(current->pid, &g_super.status, 0);
			prev = current;
			current = current->next;
		}
	}
	return ;
}
*/
