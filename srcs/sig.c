/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:41:45 by jwilliam          #+#    #+#             */
/*   Updated: 2022/11/22 16:04:24 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

void	sig_handler_int(int sig_num)
{
	if (sig_num == SIGINT)
	{
		g_super.status = 130;
		//ioctl(STDIN_FILENO, TIOCSTI, "\n");
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
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
