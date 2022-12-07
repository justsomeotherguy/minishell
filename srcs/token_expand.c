/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:28:25 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/07 16:30:56 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

char	*make_expanded_str(char *token, char *envdat)
{
	int		i;
	int		j;
	int		k;
	char	*new;

	dprintf(2, "input envdat - '%s'\n", envdat);
	i = 0;
	j = 0;
	k = 0;
	if (check_for_dollar(token) == 0)
		return (token);
	if (envdat)
		new = malloc(sizeof(char) * (ft_strlen(token) + ft_strlen(envdat)));
	else
		new = malloc(sizeof(char) * ft_strlen(token));
	if (!new)
		return (NULL);
	while (token[i] != '\0' && token[i] != '$')
	{
		new[k] = token[i];
		i++;
		k++;
	}
	if (envdat)
	{
		while (envdat[j] != '\0')
		{
			new[k] = envdat[j];
			j++;
			k++;
		}
	}
	i += get_envarname_length(&token[i]);
	while (token[i] != '\0')
	{
		new[k] = token[i];
		i++;
		k++;
	}
	new[k] = '\0';
	free(token);
	return (new);
}

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
			tokens[i] = make_expanded_str(tokens[i],
					get_envar(tokens[i]));
			tokens[i] = check_to_trim(tokens[i]);
		}
		else
			tokens[i] = make_expanded_str(tokens[i],
					get_envar(tokens[i]));
		i++;
	}
}
