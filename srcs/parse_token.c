/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:55:52 by jwilliam          #+#    #+#             */
/*   Updated: 2022/10/18 17:50:41 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

static int	set_filein(char *filein)
{
	
}

static int	set_fileout(char *fileout)
{

}

static int	count_pipes(void)
{
	int		count;
	int		j;

	count = 0;
	j = 0;
	while (g_super.full_tokens[j])
	{
		if (g_super.full_tokens[j] == "|")
			count++;
		j++;
	}
	return (count);
}

void	parse_token(void)
{
	int		pipe_count;
	int		tk;
	int		i;
	int		j;

	pipe_count = count_pipes();
	tk = 0;
	i = 0;
	j = 0;
	if (pipe_count != 0)
	{
		g_super.cmds = malloc(sizeof(char *) * pipe_count + 1);
		while (g_super.full_tokens[tk])
		{
			if (ft_strcmp(g_super.full_tokens[tk], "|") == 0)
			{
				g_super.cmds[j]->tokens[i] = '\0';
				i = 0;
				j++;
			}
			else
			{
				g_super.cmds[j]->tokens[i] = ft_strdup(g_super.full_tokens[tk]);
				i++;
				tk++;
			}
		}
		g_super.cmds[j]->tokens[i] = '\0';
		g_super.cmds[j + 1] = 0;
	}
	else
	{
		g_super.cmds = malloc(sizeof(char *) + 1);
		g_super.cmds[0]->tokens = g_super.full_tokens;
	}
}
