/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:04:40 by cgermain          #+#    #+#             */
/*   Updated: 2023/11/10 11:04:42 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_errnum;

void	signal_handler(int signum)
{
	if(signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_errnum = 130;
}

void	signal_handler_child(int signum)
{
	if(signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_errnum = 130;
}

void	signal_loop(t_data	*data)
{
	(void) data;
	signal(SIGINT,  signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

