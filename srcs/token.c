/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:16:52 by jwilliam          #+#    #+#             */
/*   Updated: 2022/10/07 16:10:58 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

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

char	**make_tokens(char *line)
{
	char	**tokens;
	int		i;
	int		tk;
	int		j;

	tokens = malloc(sizeof(char *) * (get_line_length(line) + 1));
	if (!tokens || !line)
		return (NULL);
	i = 0;
	tk = 0;
	j = 0;
	while (line[i] != '\0')
	{
		while (line[i] == ' ' || line[i] == '\t')
		{
			i++;
		}
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
	expand_tokens(tokens);
	return (tokens);
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
	t_envar	*test;

	i = -1;
	while (tokens[++i])
	{
		j = 0;
		if (tokens[i][j] == '\'')
			continue ;
		while (tokens[i][j] != '\0')
		{
			if (tokens[i][j] == '$')
			{
				test = find_env(g_super.envar, (tokens[i] + 1));
				if (test != NULL)
					tokens[i] = (char *)test->data;
			}
			j++;
		}
	}
}
