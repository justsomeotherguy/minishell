/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:36:29 by jwilliam          #+#    #+#             */
/*   Updated: 2022/10/26 15:44:03 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

static int	set_filein(t_cmdset *current, char *filein)
{
	int		f_in;
	int		i;
	char	**trim;

	f_in = open(filein, O_RDONLY);
	while (current->tokens)
		i++;
	trim = (char **)malloc(sizeof(char *) * (i - 1));

	return (f_in);
}

static int	set_fileout(t_cmdset *current, char *fileout)
{
	int		f_out;

	f_out = open(fileout, O_RDWR | O_CREAT | O_TRUNC, 0644);
	return (f_out);
}

static void	do_process(char **paths, t_cmdset *current, int *fd)
{
	char	*exec_path;

	if (current->fd_in != STDIN_FILENO)
	{
		if (dup2(current->fd_in, STDIN_FILENO) == -1)
		{
			printf("in dup error\n");
			return ;
		}
		close(current->fd_in);
	}
	if (current->fd_out != STDOUT_FILENO)
	{
		if (dup2(current->fd_out, STDOUT_FILENO) == -1)
		{
			printf("out dup error\n");
			return ;
		}
		close(current->fd_out);
	}
	if (is_builtin(current->tokens) >= 0)
		do_builtin(is_builtin(current->tokens), current->tokens);
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
	if (execve(exec_path, current->tokens, NULL) == -1)
	{
		printf("Unable to execute command\n");
		exit(1);
	}
	exit(0);
}

static t_cmdset	*has_redirect(void)
{

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
		j = 0;
		while (current->tokens[j])
		{
			if (ft_strcmp(current->tokens[j], "<") == 0)
			{
				if (current->tokens[j + 1])
					set_filein(current, current->tokens[j + 1]);
			}
			else if (ft_strcmp(current->tokens[j], ">") == 0)
			{
				if (current->tokens[j + 1])
					set_fileout(current, current->tokens[j + 1]);
			}
			j++;
		}
		fd[0] = current->fd_in;
		fd[1] = current->fd_out;
		if (pipe(fd) == -1)
			printf("Pipe Error");
		current->pid = fork();
		if (current->pid < 0)
		{
			close(fd[0]);
			close(fd[1]);
			printf("Fork Error");
			return ;
		}
		if (current->pid == 0)
			do_process(paths, current, fd);
		if (waitpid(current->pid, NULL, 0) < 0)
			printf("Process error\n");
		current = current->next;
	}
}
