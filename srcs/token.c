/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:16:52 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/03 21:11:00 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

int	get_last_quote(char const *line, char c)
{
	int		i;
	int		mark;

	i = ft_strlen(line);
	mark = 0;
	while (i > 0)
	{
		if (line[i] == c)
		{
			mark = i;
			break ;
		}
		i--;
	}
	if (i == 0)
		return (ft_strlen(line));
	else
		return (mark + 1);
}

int	token_length(char const *line)
{
	int		len;
	int		count;
	char	c;

	len = 0;
	count = 0;
	while (line[len] != '\0')
	{
		if ((line[len] == 34 || line[len] == 39) && count == 0)
		{
			c = line[len];
			count = count_start_quotes((char *)line, c);
			len += count;
			while (line[len] != '\0' && count > 0)
			{
				if (line[len] == c)
					count--;
				len++;
			}
		}
		if (line[len] == ' ' || line[len] == '\0')
			break ;
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
	while (i < length)
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
		if (i == 0 && (line[i] >= 33 && line[i] < 127))
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
			&& (line[i + 1] >= 33 && line[i + 1] < 127))
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
	expand_tokens(tokens);
	return (tokens);
}
