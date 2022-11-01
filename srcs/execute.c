/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:36:29 by jwilliam          #+#    #+#             */
/*   Updated: 2022/11/02 00:23:15 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

static int	set_filein(t_cmdset *current, char *filein)
{
	int		f_in;
	int		i;
	int		j;
	char	**trim;

	f_in = open(filein, O_RDONLY);
	i = 0;
	j = 0;
	while (current->tokens)
		j++;
	trim = (char **)malloc(sizeof(char *) * (j - 1));
	j = 0;
	while (current->tokens[j] && trim[i])
	{
		if (ft_strcmp(current->tokens[j], "<") == 0)
			j += 2;
		if (current->tokens[j])
			trim[i] = ft_strdup(current->tokens[j]);
		else
			break ;
		i++;
		j++;
	}
	trim[i] = 0;
	free_2d_array(current->tokens);
	current->tokens = trim;
	return (f_in);
}

static int	set_fileout(t_cmdset *current, char *fileout)
{
	int		f_out;
	int		i;
	int		j;
	char	**trim;

	f_out = open(fileout, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	i = 0;
	j = 0;
	while (current->tokens[j])
		j++;
	trim = (char **)malloc(sizeof(char *) * (j - 1));
	j = 0;
	while (current->tokens[j])
	{
		printf("filout token %s\n", current->tokens[j]);
		if (ft_strcmp(current->tokens[j], ">") == 0)
			j += 2;
		if (current->tokens[j])
			trim[i] = ft_strdup(current->tokens[j]);
		else
			break ;
		printf("trim filout token %s\n", trim[i]);
		i++;
		j++;
	}
	trim[i] = 0;
	free_2d_array(current->tokens);
	current->tokens = trim;
	return (f_out);
}

static void	pipe_proc(t_cmdset *current, int *fd)
{
	char	**paths;
	char	*exec_path;

	paths = init_pathlist();
	exec_path = get_path_for_cmd(paths, current->tokens[0]);
	close(fd[0]);
	close(fd[1]);
	if (current->fd_in != 0)
		close(current->fd_in);
	if (current->fd_out != 1)
		close(current->fd_out);
	if (execve(exec_path, current->tokens, NULL) == -1)
	{
		printf("Unable to execute command\n");
		return ;
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

static int	set_fd_in(t_cmdset *current)
{
	int		j;

	j = 0;
	while (current->tokens[j])
	{
		if (ft_strcmp(current->tokens[j], "<") == 0)
		{
			if (current->tokens[j + 1])
			{	
				current->fd_in = set_filein(current, current->tokens[j + 1]);
				return (1);
			}
		}
		j++;
	}
	return (0);
}

static int	set_fd_out(t_cmdset *current)
{
	int		j;

	j = 0;
	while (current->tokens[j])
	{	
		if (ft_strcmp(current->tokens[j], ">") == 0)
		{
			if (current->tokens[j + 1])
			{	
				current->fd_out = set_fileout(current, current->tokens[j + 1]);
				return (1);
			}
		}
		j++;
	}
	return (0);
}

void	executor(void)
{
	t_cmdset	*current;
	int			fd[2];

	current = g_super.cmds;
	while (current)
	{
		if (set_fd_in(current) == 1)
		{
			if (dup2(current->fd_in, STDIN_FILENO) == -1)
				return ;
			close(current->fd_in);
		}
		set_fd_out(current);
		if (pipe(fd) == -1)
			return ;
		current->pid = fork();
		if (current->pid == -1)
			return ;
		if (current->pid == 0)
			pipe_proc(current, fd);
		close(fd[1]);
		waitpid(current->pid, NULL, 0);
		close(fd[0]);
		current = current->next;
	}
}
/*
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