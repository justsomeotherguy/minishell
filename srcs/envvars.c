/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:58:33 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/02 16:21:59 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

/*
Creates the initial environment variable list from the envp arguments
received from the main function.
*/
void	set_env(char **envp)
{
	int			i;	
	char		**envp_split;

	i = 0;
	while (envp[i])
	{
		envp_split = ft_split(envp[i], '=');
		add_env(&g_super.envar, new_env(envp_split[0], envp_split[1]));
		free(envp_split);
		i++;
	}
}

void	print_env(void)
{
	t_envar		*temp;

	temp = g_super.envar;
	while (temp)
	{
		printf("%s = %s\n", temp->name, (char *)temp->data);
		temp = temp->next;
	}
	g_super.status = 0;
	return ;
}

static int	count_envars(t_envar *envars)
{
	t_envar		*temp;
	int			i;

	temp = envars;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	rebuild_envar_arr(void)
{
	char		**new_arr;
	t_envar		*temp;
	int			num;
	int			j;

	if (g_super.envar_arr != NULL)
		free(g_super.envar_arr);
	temp = g_super.envar;
	num = count_envars(temp);
	j = 0;
	new_arr = malloc(sizeof(char *) * num + 1);
	if (!new_arr)
		return ;
	while (j < num)
	{
		new_arr[j] = ft_strdup(temp->name);
		new_arr[j] = ft_strjoin(new_arr[j], "=");
		new_arr[j] = ft_strjoin(new_arr[j], temp->data);
		j++;
		temp = temp->next;
	}
	new_arr[j] = NULL;
	g_super.envar_arr = new_arr;
	return ;
}
