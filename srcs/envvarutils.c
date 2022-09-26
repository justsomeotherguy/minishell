/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvarutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:31:15 by jwilliam          #+#    #+#             */
/*   Updated: 2022/09/26 16:39:24 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envar	*new_env(char *name, void *data)
{
	t_envar		*new;

	new = (t_envar *)malloc(sizeof(t_envar));
	if (!new)
		return (NULL);
	new->name = name;
	new->data = data;
	new->next = NULL;
	return (new);
}

void	add_env(t_envar **envars, t_envar *new)
{
	t_envar		*add;

	if (!new)
		return ;
	if (!*envars)
		*envars = new;
	else
	{
		add = to_last(*envars);
		add->next = new;
	}
}

t_envar	*to_last(t_envar *envars)
{
	if (!envars)
		return (NULL);
	while (envars)
	{
		if (!envars->next)
			return (envars);
		envars = envars->next;
	}
	return (envars);
}