/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_setfds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:15:49 by jwilliam          #+#    #+#             */
/*   Updated: 2022/11/08 16:31:13 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

static	char	**trim_tokens(t_cmdset *current, char *redirector)
{
	t_cmdset	*temp;
	char		**trim;
	int			i;
	int			j;

	temp = current;
	i = 0;
	j = 0;
	while (temp->tokens[j])
		j++;
	trim = (char **)malloc(sizeof(char *) * (j - 1));
	j = 0;
	while (temp->tokens[j] && trim[i])
	{
		if (ft_strncmp(temp->tokens[j], redirector, ft_strlen(redirector)) == 0)
			j += 2;
		if (temp->tokens[j])
			trim[i] = ft_strdup(temp->tokens[j]);
		else
			break ;
		i++;
		j++;
	}
	trim[i] = 0;
	return (trim);
}

int	set_filein(t_cmdset *current, char *filein)
{
	int		f_in;
	char	**trim;

	trim = trim_tokens(current, "<");
	free_2d_array(current->tokens);
	current->tokens = trim;
	return (f_in);
}

int	set_fileout(t_cmdset *current, char *fileout, int set)
{
	int		f_out;
	char	**trim;

	if (set == 0)
	{
		f_out = open(fileout, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		trim = trim_tokens(current, ">");
		free_2d_array(current->tokens);
		current->tokens = trim;
		return (f_out);
	}
	else if (set == 1)
	{
		f_out = open(fileout, O_CREAT | O_RDWR | O_APPEND, 0777);
		trim = trim_tokens(current, ">>");
		free_2d_array(current->tokens);
		current->tokens = trim;
		return (f_out);
	}
	return (1);
}

int	set_fd_in(t_cmdset *current)
{
	t_cmdset	*temp;
	int			j;

	temp = current;
	j = 0;
	while (temp->tokens[j])
	{
		if (ft_strcmp(temp->tokens[j], "<") == 0)
		{
			if (temp->tokens[j + 1])
			{	
				temp->fd_in = set_filein(temp, temp->tokens[j + 1]);
				return (1);
			}
		}
		j++;
	}
	return (0);
}

int	set_fd_out(t_cmdset *current)
{
	t_cmdset	*temp;
	int			j;

	temp = current;
	j = -1;
	while (temp->tokens[++j])
	{	
		if (ft_strncmp(temp->tokens[j], ">>", 2) == 0)
		{
			if (temp->tokens[j + 1])
			{	
				temp->fd_out = set_fileout(temp, temp->tokens[j + 1], 1);
				return (1);
			}
		}
		else if (ft_strncmp(temp->tokens[j], ">", 1) == 0)
		{
			if (temp->tokens[j + 1])
			{	
				temp->fd_out = set_fileout(temp, temp->tokens[j + 1], 0);
				return (1);
			}
		}
	}
	return (0);
}
