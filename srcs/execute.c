/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:36:29 by jwilliam          #+#    #+#             */
/*   Updated: 2022/10/13 15:34:20 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

static void	do_process(char **paths, char **tokens)
{
	char	*exec_path;

	if (!paths)
	{
		printf("Unable to build PATH\n");
		exit(1);
	}
	exec_path = get_path_for_cmd(paths, tokens[0]);
	if (!exec_path)
	{
		printf("Unable to find command\n");
		exit(1);
	}
	if (execve(exec_path, tokens, NULL) == -1)
	{
		printf("Unable to execute command\n");
		exit(1);
	}
}

void	executor(char **tokens)
{
	char	**paths;
	int		pid;

	paths = init_pathlist();
	pid = fork();
	if (pid == -1)
		printf("Fork Error");
	if (pid == 0)
		do_process(paths, tokens);
	if (waitpid(pid, NULL, 0) < 0)
		printf("Process error\n");
}
