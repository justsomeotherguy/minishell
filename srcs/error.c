/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:05:47 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/03 13:34:24 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

void	error_message(char *message, int status)
{
	ft_putstr_fd("Error : ", 2);
	ft_putendl_fd(message, 2);
	g_super.status = status;
	return ;
}

void	error_message_and_exit(char *message, int status)
{
	ft_putstr_fd("Error : ", 2);
	ft_putendl_fd(message, 2);
	exit(status);
}

void	mini_perror(void)
{
	perror("Error ");
	exit(EXIT_FAILURE);
}
