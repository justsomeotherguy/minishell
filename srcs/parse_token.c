/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:55:52 by jwilliam          #+#    #+#             */
/*   Updated: 2022/10/21 14:35:56 by jwilliam         ###   ########.fr       */
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

static int	count_tokens(int pos)
{
	int		i;

	i = 0;
	while (g_super.full_tokens[pos])
	{
		if (ft_strcmp(g_super.full_tokens[pos], "|") == 0)
			break ;
		i++;
		pos++;
	}
	return (i);
}

void	parse_token(void)
{
	t_cmdset	*temp;
	int			tk;
	int			i;

	tk = 0;
	i = 0;
	temp = new_cmdset();
	temp->tokens = (char **)malloc(sizeof(char *) * (count_tokens(tk) + 1));
	while (g_super.full_tokens[tk])
	{
		if (ft_strcmp(g_super.full_tokens[tk], "|") == 0)
		{
			temp->tokens[i] = 0;
			add_cmdset(&g_super.cmds, temp);
			temp = new_cmdset();
			temp->tokens = (char **)malloc(sizeof(char *)
					* (count_tokens(tk + 1) + 1));
			i = 0;
		}
		else
		{
			temp->tokens[i] = ft_strdup(g_super.full_tokens[tk]);
			i++;
		}
		tk++;
	}
	temp->tokens[i] = 0;
	add_cmdset(&g_super.cmds, temp);
}
