/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:58:33 by jwilliam          #+#    #+#             */
/*   Updated: 2022/09/26 16:40:20 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(char **envp)
{
	t_super		g_super;
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
	t_super		g_super;
	t_envar		*temp;

	temp = g_super.envar;
	while (temp)
	{
		printf("%s\n", (char *)temp->data);
		temp = temp->next;
	}
}
