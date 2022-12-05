/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:16:52 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/05 19:59:34 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

int	token_length(char const *line)
{
	int		len;

	dprintf(2, "token length received string %s\n", line);
	len = 0;
	if (line[len] == 34)
	{
		len++;
		while (line[len] != 34 && line[len + 1] != '\0')
			len++;
		return (len + 1);
	}
	else if (line[len] == 39)
	{
		len++;
		while (line[len] != 39 && line[len + 1] != '\0')
			len++;
		return (len + 1);
	}
	else
	{
		while (line[len + 1] != ' ' && line[len] != '\0')
			len++;
	}
	return (len);
}

char	*make_token(char *line)
{
	char	*tk;
	int		i;
	int		length;

	i = 0;
	length = token_length(line);
	tk = malloc(sizeof(char) * (length + 1));
	while (i <= length)
	{
		tk[i] = line[i];
		i++;
	}
	tk[i] = '\0';
	return (tk);
}

int	count_tokens(char const *line, int count)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (i == 0 && (line[i] >= 33 && line[i] <= 127))
			count++;
		if (line[i] == 34)
		{
			i++;
			while (line[i] != 34 && line[i + 1] != '\0')
				i++;
		}
		else if (line[i] == 39)
		{
			i++;
			while (line[i] != 39 && line[i + 1] != '\0')
				i++;
		}
		else if ((line[i] == ' ' || line[i] == '\t')
			&& (line[i + 1] >= 33 && line[i + 1] <= 127))
			count++;
		i++;
	}
	return (count);
}

char	**make_tokens(char *line)
{
	char	**tokens;
	int		tkcount;
	int		i;
	int		j;

	tkcount = 0;
	i = 0;
	j = 0;
	tokens = malloc(sizeof(char *) * (count_tokens(line, tkcount) + 1));
	if (!tokens)
		return (NULL);
	while (line[i] != '\0')
	{
		if (line[i] >= 33 && line[i] <= 126)
		{
			tokens[j] = make_token(&line[i]);
			i += (ft_strlen(tokens[j]) - 1);
			j++;
		}
		i++;
	}
	tokens[j] = 0;
	for (int l = 0; tokens[l]; l++)
		dprintf(2, "tokens before expanding - '%s'\n", tokens[l]);
	expand_tokens(tokens);
	return (tokens);
}

/*
int	get_line_length(char *line)
{
	int		len;
	int		i;
	int		quote_flip;

	len = 0;
	i = 0;
	quote_flip = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 34 || line[i] == 39)
		{
			if (quote_flip == 0)
				quote_flip = 1;
			else
				quote_flip = 0;
		}
		if (line[i] == ' ' && quote_flip == 1)
			len++;
		if (line[i] >= 33 && line[i] <= 126)
			len++;
		i++;
	}
	return (len);
}
*/

/*
int	token_length(char const *line)
{
	int		len;
	int		quote_flip;

	len = 0;
	quote_flip = 0;
	if (is_meta(line[len], line[len + 1]) > 0)
		return (is_meta(line[len], line[len + 1]));
	while (line[len] != '\0')
	{
		if (quote_flip == 0 && is_meta(line[len], line[len + 1]) > 0)
			return (len);
		if (line[len] == 34 || line[len] == 39)
		{
			if (quote_flip == 0 && len > 0)
				return (len);
			else if (quote_flip == 0 && len == 0)
				quote_flip = 1;
			else
				return (len + 1);
		}
		if ((line[len] == ' ' || line[len] == '\t') && quote_flip == 0)
			break ;
		len++;
	}
	return (len);
}
*/

/*
char	**make_tokens(char *line)
{
	char	**tokens;
	int		i;
	int		tk;

	tokens = malloc(sizeof(char **) * (get_line_length(line) + 1));
	if (!tokens || !line)
		return (NULL);
	i = 0;
	tk = 0;
	while (line[i] != '\0')
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] >= 33 && line[i] <= 126)
		{
			tokens[tk] = make_token(&line[i]);
			if (get_line_length(tokens[tk]) == 1
				&& (tokens[tk][0] == 34 || tokens[tk][0] == 39))
				exit(-1); //TODO add error message
			i += ft_strlen(tokens[tk]) - 1;
			tk++;
		}
		i++;
	}
	tokens[tk] = 0;
	for (int l = 0; tokens[l] != 0; l++)
		dprintf(2, "token[%i] - %s\n", l, tokens[l]);
	expand_tokens(tokens);
	return (tokens);
}
*/
