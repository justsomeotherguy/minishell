/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:55:52 by jwilliam          #+#    #+#             */
/*   Updated: 2022/10/19 16:28:09 by jwilliam         ###   ########.fr       */
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
		if (ft_strcmp(g_super.full_tokens[j], "|") == 0)
			count++;
		j++;
	}
	return (count);
}

static char	**allocate_cmds(void)
{
	char	**cmds;
	int		i;
	int		j;
	int		tk;

	i = 1;
	j = 0;
	tk = 0;
	while (g_super.full_tokens[tk])
	{
		if (ft_strcmp(g_super.full_tokens[tk], "|") == 0)
		{
			g_super.cmds[j].tokens = ft_calloc(i + 1, sizeof(char *));
			j++;
			i = 1;
		}
		i++;
		tk++;
	}
	return (cmds);
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
	printf("pipes %i\nparse token\n", pipe_count);
	g_super.cmds = ft_calloc((pipe_count + 2), sizeof(t_cmdset));
	if (pipe_count > 0)
	{
		allocate_cmds();
		while (g_super.full_tokens[tk])
		{
			printf("current parsing token %s\n", g_super.full_tokens[tk]);
			if (ft_strcmp(g_super.full_tokens[tk], "|") == 0)
			{
				g_super.cmds[j].tokens[i] = 0;
				i = 0;
				j++;
			}
			else
			{
				g_super.cmds[j].tokens[i] = ft_strdup(g_super.full_tokens[tk]);
				printf("cmd set %i, token %s\n", j, g_super.cmds[j].tokens[i]);
				i++;
			}
			tk++;
		}
	}
	else
	{
		allocate_cmds();
		g_super.cmds[0].tokens = g_super.full_tokens;
	}
	free(g_super.full_tokens);
}
