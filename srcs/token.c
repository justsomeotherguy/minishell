/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:16:52 by jwilliam          #+#    #+#             */
/*   Updated: 2022/09/26 15:38:55 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (line[len] != '\0')
	{
		if (line[len] == 34 || line[len] == 39)
		{
			if (quote_flip == 0)
				quote_flip = 1;
			else
			{
				len++;
				break ;
			}		
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

	i = 0;
	tk = malloc(sizeof(char) * (token_length(line) + 1));
	if (line[i] == 34 || line[i] == 39)
	{
		tk[i] = line[i];
		i++;
		while (line[i] != '\0' && (line[i] != 34 || line[i] == 39))
		{
			tk[i] = line[i];
			i++;
		}
		tk[i] = line[i];
		i++;
	}
	else
	{
		while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t')
		{
			tk[i] = line[i];
			i++;
		}
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
			i += ft_strlen(tokens[tk]);
			tk++;
		}
		i++;
	}
	tokens[tk] = 0;
	while (tokens[j])
	{
		printf("%s\n", tokens[j]);
		j++;
	}
	return (tokens);
}
