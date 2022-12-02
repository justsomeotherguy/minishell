/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:28:25 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/02 16:28:59 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

char	*expand_str(char *token, int pos)
{
	int		i;
	int		j;
	int		k;
	char	*str;
	char	*new;

	i = 0;
	j = 0;
	k = 0;
	str = get_envar((ft_strchr(token, '$') + 1));
	if (str)
		printf("str - %s\n", str);
	else
		printf("nothing here\n");
	new = malloc(sizeof(char) * (ft_strlen(token)
				- get_envarname_length(ft_strchr(token, '$') + 1))
			+ ft_strlen(str));
	while (token[i])
	{
		if (token[i] == '$')
		{
			if (ft_strlen(str) > 0)
			{
				while (str[j] != '\0')
				{
					new[k] = str[j];
					k++;
					j++;
				}
				i += get_envarname_length(token + i);
			}
			else
			{
				new[k] = ' ';
				k++;
				i += get_envarname_length(token + i);
			}
		}
		new[k] = token[i];
		i++;
		k++;
	}
	new[k] = '\0';
	free(token);
	if (str)
		free(str);
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
	//t_envar	*test;

	i = -1;
	while (tokens[++i])
	{
		j = 0;
		i = trimquotes(tokens, i);
		while (tokens[i] && tokens[i][j] != '\0')
		{
			if (tokens[i][j] == '$')
			{
				tokens[i] = expand_str(tokens[i], j);
				printf("%s\n", tokens[i]);
				j = -1;
			}
			j++;
		}
	}
}
