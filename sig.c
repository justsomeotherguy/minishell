/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:41:45 by jwilliam          #+#    #+#             */
/*   Updated: 2022/09/21 14:55:48 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "teststuff.h"

void	sig_handler_int(int sig_num)
{
	int	i;

	i = sig_num;
	signal(SIGINT, sig_handler_int);
	printf("SIGINT\n");
}

void	sig_handler_quit(int sig_num)
{
	int	i;

	i = sig_num;
	signal(SIGINT, sig_handler_quit);
	printf("SIGQUIT\n");
}
