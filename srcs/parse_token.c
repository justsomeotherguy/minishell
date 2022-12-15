/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:55:52 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/15 13:37:29 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

static int	count_pipes(int pos)
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

static void	do_parsing(t_cmdset *temp)
{
	int		tk;
	int		i;

	tk = 0;
	i = 0;
	while (g_super.full_tokens[tk])
	{
		if (ft_strncmp(g_super.full_tokens[tk], "|", 1) == 0)
		{
			temp->tokens[i] = 0;
			add_cmdset(&g_super.cmds, temp);
			temp = new_cmdset();
			temp->tokens = malloc(sizeof(char *) * (count_pipes(tk + 1) + 1));
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
	return ;
}

static void	set_cmd_nums(void)
{
	int			i;
	t_cmdset	*current;

	i = 0;
	current = g_super.cmds;
	while (current)
	{
		current->cmd_no = i;
		i++;
		current = current->next;
	}
}

void	parse_token(void)
{
	t_cmdset	*temp;
	int			tk;
	int			i;

	tk = 0;
	temp = new_cmdset();
	temp->tokens = malloc(sizeof(char *) * (count_pipes(tk) + 1));
	do_parsing(temp);
	set_cmd_nums();
	return ;
}
