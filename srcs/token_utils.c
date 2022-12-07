/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:56:38 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/07 16:12:27 by jwilliam         ###   ########.fr       */
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
	return (0);
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
	getname = ft_substr(token, (check_for_dollar(token) + 1),
			get_envarname_length(token + (check_for_dollar(token) + 1)));
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
	while (token[i] != '\0' && token[i] != ' '
		&& token[i] != 34 && token[i] != 39)
		i++;
	return (i);
}

char	*trim_quotes(char *str, char c)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	dprintf(2, "start trimming for %c\n", c);
	new = malloc(sizeof(char) * ft_strlen(str));
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}
