/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:56:38 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/16 15:10:13 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

int	check_for_dollar(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

int	check_quotes(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34)
		{
			dprintf(2, "found double quote\n");
			return (1);
		}
		else if (str[i] == 39)
		{
			dprintf(2, "found single quote\n");
			return (2);
		}
		i++;
	}
	return (0);
}

char	*get_envar(char *token)
{
	t_envar	*temp;
	char	*getname;

	if (!token)
		return (NULL);
	if (token[0] == '?')
		return (ft_itoa(g_super.status));
	getname = ft_substr(token, 0, get_envarname_length(token));
	dprintf(2, "getname substr - '%s'\n", getname);
	temp = find_env(g_super.envar, getname);
	free(getname);
	if (temp)
		return ((char *)ft_strdup(temp->data));
	else
		return (NULL);
}

int	get_envarname_length(char *token)
{
	int		i;

	i = 0;
	if (token[0] == '?')
		return (1);
	while (token[i] != '\0' && token[i] != ' ' && token[i] != 34
		&& token[i] != 39)
		i++;
	return (i);
}

char	*check_to_trim(char *token)
{
	int		i;
	char	*new;

	if (check_quotes(token) == 2)
	{
		new = trim_quotes(token, 39);
		free(token);
		token = new;
		return (token);
	}
	else if (check_quotes(token) == 1)
	{
		new = trim_quotes(token, 34);
		free(token);
		token = new;
		return (token);
	}
	else
		return (token);
}
