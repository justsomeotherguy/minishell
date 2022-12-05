/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:28:54 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/05 13:59:30 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_super		g_super;

int	get_heredoc(char *end)
{
	char	*line;
	int		fd[2];

//	make_signal();
	if (pipe(fd) < 0)
		return (-1); // to do error
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			return (1);
		if (ft_strcmp(line, end) == 0)
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
	}
	close(fd[1]);
	return (fd[0]);
}
