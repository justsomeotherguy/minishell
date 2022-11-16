/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:56:38 by jwilliam          #+#    #+#             */
/*   Updated: 2022/11/14 16:07:53 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

int	is_between_quote(char *token, int pos)
{
	int		i;
	int		j;

	i = pos;
	j = pos;
	while (i > 0)
	{
		if (token[i] == '\'')
			break ;
		if (i == 0 && token[i] != '\'')
			return (0);
		i--;
	}
	while (token[j] != '\0')
	{
		if (token[j] == '\'')
			break ;
		if (token[j] == '\0')
			return (0);
		j++;
	}
	return (1);
}