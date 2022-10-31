/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:36:29 by jwilliam          #+#    #+#             */
/*   Updated: 2022/10/31 20:27:42 by jwilliam         ###   ########.fr       */
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
		if (execve(exec_path, current->tokens, NULL) == -1)
		{
			printf("Unable to execute command\n");
			exit(1);
		}
	}
	waitpid(current->pid, NULL, 0);
	return ;
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
				{	
					current->fd_in = set_filein(current, current->tokens[j + 1]);
					dup2(fd[0], current->fd_in);
					close(fd[0]);
					j = -1;
				}
			}
			else if (ft_strcmp(current->tokens[j], ">") == 0)
			{
				if (current->tokens[j + 1])
				{	
					current->fd_out = set_fileout(current, current->tokens[j + 1]);
					dup2(fd[1], current->fd_out);
					close(fd[1]);
					j = -1;
				}
			}
			j++;
		}
		if (pipe(fd) == -1)
			printf("Pipe Error");
		do_process(paths, current, fd);
		current = current->next;
//		close(fd[1]);
	}
}
