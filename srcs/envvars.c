/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:58:33 by jwilliam          #+#    #+#             */
/*   Updated: 2022/11/14 14:35:42 by jwilliam         ###   ########.fr       */
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
}
