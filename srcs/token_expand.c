/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:28:25 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/14 14:26:36 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

void	replace_strings(char **split)
{
	char	*temp;
	int		i;

	i = 0;
	while (split[i] != NULL)
	{
		dprintf(2, "split word [%i] - '%s'\n", i, split[i]);
		i++;
	}
	return ;
}

char	*add_expanded_str(char *new, char *token, int pos, int i)
{
	int		k;
	char	*getdat;
	char	*temp;

	k = 0;
	getdat = get_envar(&token[i]);
//	dprintf(2, "add getdat - %s\n", getdat);
	if (!getdat)
		return (new);
	temp = malloc(sizeof(char) * (ft_strlen(token) + ft_strlen(getdat)));
	ft_memcpy(temp, new, pos);
	while (getdat[k] != '\0')
	{
		temp[pos + k] = getdat[k];
		k++;
	}
	free(new);
	return (temp);
}

char	*make_expanded_str(char *token)
{
	int		i;
	int		j;
	char	*new;
	char	**split;

	i = 0;
	j = 0;
	if (check_for_dollar(token) < 0)
		return (token);
	split = ft_split(token, '$');
	replace_strings(split);
//	new[j] = '\0';
	free(split);
//	free(token);
	return (token);
}

char	*check_to_trim(char *token)
{
	int		i;
	char	*new;

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
	while (tokens[i] != NULL)
	{
		if (check_quotes(tokens[i]) == 2)
			tokens[i] = check_to_trim(tokens[i]);
		else if (check_quotes(tokens[i]) == 1)
		{
			tokens[i] = make_expanded_str(tokens[i]);
			tokens[i] = check_to_trim(tokens[i]);
		}
		else
			tokens[i] = make_expanded_str(tokens[i]);
		i++;
	}
}
