/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:36:29 by jwilliam          #+#    #+#             */
/*   Updated: 2022/11/25 15:33:18 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

static int	ft_dup2(int old, int new)
{
	if (dup2(old, new) < 0)
		return (-1);
	else
		close(old);
	return (0);
}

static void	pipe_exec(t_cmdset *current)
{
	char	**paths;
	char	*exec_path;

	if (current->next)
	{
		close(current->pipefd[0]);
		close(current->pipefd[1]);
	}
	if (is_builtin(current->tokens) > 0)
		do_builtin(is_builtin(current->tokens), current->tokens);
	else
	{
		paths = init_pathlist();
		if (!paths)
			exit(1); // to_do error
		exec_path = get_path_for_cmd(paths, current->tokens[0]);
		if (!exec_path)
			exit(1); // to_do error
		if (execve(exec_path, current->tokens, g_super.envar_arr) == -1)
		{
			printf("Unable to execute command\n");
			exit(1); // to_do error
		}
	}
	return ;
}

/*
static void	do_process(char **paths, t_cmdset *current, int *fd)
{
	char	*exec_path;


	if (is_builtin(current->tokens) >= 0)
	{
		do_builtin(is_builtin(current->tokens), current->tokens);
		return ;
	}
	if (!paths)
	{
		printf("Unable to build PATH\n");
		exit(1);
	}
	exec_path = get_path_for_cmd(paths, current->tokens[0]);
	if (!exec_path)
	{
		printf("%s: command not found\n", current->tokens[0]);
		exit(1);
	}
	current->pid = fork();
	if (current->pid == 0)
	{
		close(fd[1]);
		close(current->fd_in);
		close(current->fd_out);
		if (execve(exec_path, current->tokens, NULL) == -1)
		{
			printf("Unable to execute command\n");
			return ;
		}
	}
	waitpid(current->pid, NULL, 0);
	close(fd[0]);
	return ;
}
*/

void	exec_single(t_cmdset *current)
{
	char	**paths;
	char	*exec_path;

	if (is_builtin(current->tokens) > 0)
		do_builtin(is_builtin(current->tokens), current->tokens);
	else
	{
		current->pid = fork();
		if (current->pid == 0)
		{
			if (set_fd_in(current) == 1)
				if (ft_dup2(current->fd_in, STDIN_FILENO) < 0)
					exit(1); // to_do error
			if (set_fd_out(current) == 1)
				if (ft_dup2(current->fd_out, STDOUT_FILENO) < 0)
					exit(1); // to_do error
			paths = init_pathlist();
			if (!paths)
				exit(1); // to_do error
			exec_path = get_path_for_cmd(paths, current->tokens[0]);
			if (!exec_path)
				exit(1); // to_do error
			if (execve(exec_path, current->tokens, NULL) == -1)
			{
				printf("Unable to execute command\n");
				exit(1); // to_do error
			}
		}
		else
			waitpid(current->pid, &g_super.status, 0);
	}
	return ;
}

static void	set_and_dup(t_cmdset *current, t_cmdset *prev)
{
	if (current->next)
	{
		ft_putstr_fd("stdin set and dup\n", 2);
		if (set_fd_in(current) == 1)
		{
			ft_putstr_fd("fd in set and dup\n", 2);
			if (ft_dup2(current->fd_in, STDIN_FILENO) < 0)
				return ; // to_do error
		}
		else if (prev != NULL)
		{
			ft_putstr_fd("prev pipe in set and dup\n", 2);
			ft_putstr_fd("prev->pipefd[0]: ", 2);
			ft_putnbr_fd(prev->pipefd[0], 2);
			ft_putstr_fd("\n", 2);
			if (ft_dup2(prev->pipefd[0], STDIN_FILENO) < 0)
				return ; // to_do error
		}
	}
	else
	{
		ft_putstr_fd("last stdin set and dup\n", 2);
		if (set_fd_in(current) == 1)
		{
			dprintf(2, "LAST REDIR OR STDIN\n");
			if (ft_dup2(current->fd_in, STDIN_FILENO) < 0)
				return ; // to_do error
		}
		else
		{
			dprintf(2, "LAST PIPE\n");
			dprintf(2, "prev->pipefd[0]: %d\n", prev->pipefd[0]);
			if (ft_dup2(prev->pipefd[0], STDIN_FILENO) < 0)
				dprintf(2, "bbbb\n"); // to_do error
			dprintf(2, "aaa\n");
		}
		dprintf(2, "HELLOOOOOO\n");
	}
	ft_putstr_fd("stdout set and dup\n", 2);
	if (set_fd_out(current) == 1)
	{
		if (ft_dup2(current->fd_out, STDOUT_FILENO) < 0)
			return ; // to_do error
	}
	else
		if (current->next && ft_dup2(current->pipefd[1], STDOUT_FILENO) < 0)
			return ; // to_do error
}

void	executor(void)
{
	t_cmdset	*current;
	t_cmdset	*prev;

	current = g_super.cmds;
	prev = NULL;
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
				close(current->pipefd[1]);
			waitpid(current->pid, &g_super.status, 0);
			if (current->next)
				close(current->pipefd[0]);
			prev = current;
			current = current->next;
		}
	}
	return ;
}

/*
void	executor(void)
{
	t_cmdset	*current;
	int			fd[2];
	int			pid;

	current = g_super.cmds;
	while (current != NULL)
	{	
		set_fd_in(current);
		set_fd_out(current);
		if (pipe(fd) == -1)
			return ;
		if (is_builtin(current->tokens) > 0)
			do_builtin(is_builtin(current->tokens), current->tokens);
		else
		{
			pid = fork();
			if (pid == -1)
				return ;
			else if (pid == 0)
				pipe_proc(current, fd);
			else
				waitpid(pid, NULL, 0);
			close(fd[0]);
			close(fd[1]);
		}
		current = current->next;
	}
}

void	executor(void)
{
	char		**paths;
	t_cmdset	*current;
	int			fd[2];
	int			j;

	current = g_super.cmds;
	paths = init_pathlist();
	while (current)
	{

		if (pipe(fd) == -1)
			printf("Pipe Error");
		do_process(paths, current, fd);
		current = current->next;
//		close(fd[1]);
	}
}
*/
