/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:28:25 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/06 17:00:17 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;


/*
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
*/

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

char	*make_expanded_str(char *token, char *envdat)
{
	int		i;
	int		j;
	int		k;
	char	*new;

	i = 0;
	j = 0;
	k = 0;
	dprintf(2, "start make expanded str\n");
	if (!envdat)
		return (token);
	new = malloc(sizeof(char) * (ft_strlen(token) + ft_strlen(envdat)));
	if (!new)
		return (NULL);
	while (token[i] != '\0')
	{
		new[k] = token[i];
		k++;
		i++;
		if (token[i] == '$')
		{
			while (token[i] != ' ' && token[i] != '\0')
				i++;
			while (envdat[j] != '\0')
			{
				new[k] = envdat[j];
				k++;
				j++;
			}
		}
	}
	new[k] = '\0';
	free(token);
	return (new);
}
ft_memc
char	*check_to_trim(char *token)
{
	int		i;
	char	*new;
	char	*env_data;

	if (check_quotes(token) == 2)
	{
		new = trim_quotes(token, 39);
		free(token);
		return (new);
	}
	else if (check_quotes(token) == 1)
	{
		new = trim_quotes(token, 34);
		free(token);
		return (new);
	}
	else
		return (token);
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

	i = 0;
	while (tokens[i])
	{
		if (check_quotes(tokens[i]) == 2)
			tokens[i] = check_to_trim(tokens[i]);
		else if (check_quotes(tokens[i]) == 1)
		{
			tokens[i] = check_to_trim(tokens[i]);
			tokens[i] = make_expanded_str(tokens[i],
					get_envar(ft_strchr(tokens[i], '$')));
		}
		else
//			tokens[i] = make_expanded_str(tokens[i],
//					get_envar(ft_strchr(tokens[i], '$')));
		i++;
	}
}
ft_str