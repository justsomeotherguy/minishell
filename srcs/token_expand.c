/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:28:25 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/03 18:17:43 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

void	add_envar_to_str(char *token, char *new, int *i, int *j)
{
	char	*temp;
	int		k;

	k = 0;
	temp = get_envar(&token[*i + 1]);
	*i += (get_envarname_length(&token[*i + 1]) + 1);
	if (temp)
	{
		while (temp[k] != '\0')
		{
			new[*j] = temp[k];
			*j += 1;
			k++;
		}
	}
	free(temp);
	return ;
}

char	*make_expanded_str(char *token)
{
	int		i;
	int		j;
	char	*new;
	char	c;
	int		count;

	i = -1;
	j = 0;
	count = 0;
	new = ft_calloc(512, sizeof(char));
	while (token[++i] != '\0')
	{
		if ((token[i] == 34 || token[i] == 39) && count == 0)
		{
			c = token[i];
			count = count_start_quotes(&token[i], c) + 1;
		}
		if (token[i] == c && count > 0)
			count--;
		if (token[i] == '$' && (c != 39 && count > 0))
			add_envar_to_str(token, new, &i, &j);
		new[j++] = token[i];
	}
	new[j] = '\0';
	return (new);
}

char	*get_expanded_str(char *token)
{
	int		i;
	int		j;
	char	*new;
	char	*temp;

	i = 0;
	j = 0;
	if (token[0] == '~' && token[1] == '\0')
	{
		new = ft_strdup(get_envar("HOME"));
		return (new);
	}
	if (token[0] == '$')
	{
		new = get_envar(token + 1);
		return (new);
	}
	temp = make_expanded_str(token);
	free(token);
	temp = resize_new_str(temp);
	new = 0;
	new = trim_quotes(temp);
	free(temp);
	new = resize_new_str(new);
	return (new);
}

/*
Checks tokens if $ character is within it.
Checks name after $ against environment variables and replaces token with
the content of the variable.
*/
void	expand_tokens(char **tokens)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (tokens[i])
	{
		if (has_special_characters(tokens[i]) >= 0)
		{
			temp = 0;
			temp = get_expanded_str(tokens[i]);
			if (!temp)
				tokens[i] = ft_strdup("");
			else
				tokens[i] = temp;
		}
		i++;
	}
}

/*

old schidt

char	*join_split_strings(char **split)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	temp = ft_strdup("");
	while (split[i] != NULL)
	{
		temp = ft_strjoin_safe_free(temp, split[i], true, false);
		i++;
	}
	return (temp);
}

char	*join_strings(char *str, char *envdat)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str[0] == '?')
		i = 1;
	else
	{
		while (str[i] != '\0' && str[i] != ' ' && str[i] != 34 && str[i] != 39)
			i++;
	}
	if (envdat)
		temp = ft_strjoin(ft_strdup(envdat), (str + i));
	else
		temp = ft_strjoin("", (str + i));
	return (temp);
}

void	replace_split_strings(char **split)
{
	int		i;
	int		splits;
	char	*temp;

	i = 0;
	splits = 0;
	while (split[splits] != NULL)
		splits++;
	while (split[i] != NULL)
	{
		if (!(i == 0 && splits > 1))
		{
			temp = join_strings(split[i], get_envar(split[i]));
			free(split[i]);
			split[i] = ft_strdup(temp);
			free(temp);
			dprintf(2, "made joined str - %s\n", split[i]);
		}
		i++;
	}
	return ;
}
*/
