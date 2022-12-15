/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:28:25 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/15 16:25:03 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

char	*join_split_strings(char **split)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	temp = ft_strdup("");
	while (split[i] != NULL)
	{
		dprintf(2, "split[%i] in join split strings - '%s'\n", i, split[i]);
		dprintf(2, "dafuq mate - '%s'\n", temp);
		temp = ft_strjoin_safe_free(temp, split[i], true, false);
		dprintf(2, "dafuq mate - '%s'\n", temp);
		i++;
	}
	dprintf(2, "joined split string - '%s'\n", temp);
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
	{
		temp = ft_strjoin(ft_strdup(envdat), (str + i));
		dprintf(2, "join strings - '%s'\n", temp);
	}
	else
	{
		temp = ft_strjoin("", (str + i));
		dprintf(2, "join strings - '%s'\n", temp);
	}
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
	replace_split_strings(split);
	new = join_split_strings(split);
	free(split);
	free(token);
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
