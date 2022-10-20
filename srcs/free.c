/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:33:37 by jwilliam          #+#    #+#             */
/*   Updated: 2022/10/20 15:38:07 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"

void	free_cmds(t_cmdset **cmdsets)
{
	t_cmdset		*temp;
	t_cmdset		*next;

	temp = *cmdsets;
	if (!temp)
		return ;
	while (temp)
	{
		next = temp->next;
		free_2d_array(temp->tokens);
		free(temp);
		temp = next;
	}
}
