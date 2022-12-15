/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:29:59 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/15 16:09:56 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Compares two strings, returns 0 if the strings are a match, else return
the difference between the character(s) of s1 and s2.
*/
int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

/*
Checks if the input characters from a token is a redirector.
Return 2 if it is a double angle bracket redirect.
Return 1 if it is a single angle bracket redirect.
Else return 0.
*/
int	is_meta(char c, char next)
{
	if ((c == '<' && next == '<') || (c == '>' && next == '>'))
		return (2);
	else if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

char	*ft_strjoin_safe_free(char *s1, char *s2, bool f1, bool f2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (f1)
		free(s1);
	if (f2)
		free(s2);
	return (str);
}
