/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:56:38 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/06 16:55:35 by jwilliam         ###   ########.fr       */
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

char	*get_envar(char *getname)
{
	t_envar	*temp;

	if (getname[0] == '$')
		getname++;
	temp = find_env(g_super.envar, getname);
	if (temp)
		return ((char *)ft_strdup(temp->data));
	else
		return (NULL);
}

int	get_envarname_length(char *token)
{
	int		i;

	i = 0;
	while (token[i] != '\0' && token[i] != ' ')
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

int	trimquotes(char **tokens, int i)
{
	if (tokens[i][0] == '\'')
	{
		tokens[i] = ft_strtrim(tokens[i], "\'");
		i++;
	}
	if (tokens[i][0] == '\"')
		tokens[i] = ft_strtrim(tokens[i], "\"");
	return (i);
}
