/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:34:04 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/04 14:23:20 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

char	*resize_new_str(char *old)
{
	int		i;
	char	*new;

	i = ft_strlen(old);
	new = ft_calloc((i + 1), sizeof(char));
	ft_memcpy(new, old, i);
	new[i + 1] = '\0';
	free(old);
	return (new);
}

int	count_start_quotes(char *token, char quote)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (token[i] == quote && token[i] != '\0')
	{
		i++;
		count++;
	}
	return (count);
}

static void	init_ints_for_trim(int *i, int *j, int *count)
{
	*i = 0;
	*j = 0;
	*count = 0;
	return ;
}

char	*trim_quotes(char *str)
{
	int		i;
	int		j;
	int		count;
	char	*new;
	char	c;

	init_ints_for_trim(&i, &j, &count);
	new = ft_calloc(512, sizeof(char));
	if (!new)
		return (NULL);
	while (str[i] != '\0')
	{
		if ((str[i] == 34 || str[i] == 39) && count == 0)
		{
			c = str[i];
			while (str[i] == c && str[i++] != '\0')
				count++;
		}
		if (!(str[i] == c && count > 0) && str[i] != '\0')
			new[j++] = str[i];
		if (str[i++] == c)
			count--;
	}
	new[j] = '\0';
	return (new);
}

/*
int	count_nonquotes(char *str, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
			j++;
		i++;
	}
	return (j);
}
*/