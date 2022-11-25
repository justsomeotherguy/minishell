/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvarutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:31:15 by jwilliam          #+#    #+#             */
/*   Updated: 2022/11/25 15:56:10 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Initialize new t_envar list entry with input name and data to fill list
item.
*/
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

/*

*/
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
	rebuild_envar_arr();
}

/*
Gets the last node entry in the environment variables list.
*/
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

/*
Find and retrieve an entry with a matching name from the input arguments.
If the environment variable names entry matches, returns the pointer to the 
environment variable node else return NULL.
*/
t_envar	*find_env(t_envar *envars, char *name)
{
	t_envar		*temp;

	temp = envars;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->name, name) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

/*
Find and remove an entry with a matching name from the input arguments.
If the environment variable names entry matches, removes the node entry from
the environment variables.
*/
void	find_and_remove(t_envar *envars, char *var_name)
{
	t_envar		*temp;
	t_envar		*prev;
	t_envar		*store;

	temp = envars;
	prev = temp;
	if (!envars)
		return ;
	while (temp)
	{
		if (ft_strcmp(temp->name, var_name) == 0)
		{
			store = temp->next;
			prev->next = store;
			free(temp->name);
			free(temp->data);
			free(temp);
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
	rebuild_envar_arr();
}
