/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:41:45 by jwilliam          #+#    #+#             */
/*   Updated: 2022/10/14 16:28:26 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_int(int sig_num)
{
	(void)sig_num;
	write(2, "\n", 1);
//	rl_replace_line("", 0); //(Issues with library linking)
	rl_on_new_line();
	rl_redisplay();
}

/*
void	sig_handler_quit(int sig_num)
{
	int	i;

	i = sig_num;
	signal(SIGINT, sig_handler_quit);
	printf("SIGQUIT\n");
}
*/
