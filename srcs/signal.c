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

int	g_sig_handle;

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sig_handle = SIGINT;
	}	
}

void	signal_handler_exec(int signum)
{
	if (signum == SIGINT)
	{
		g_sig_handle = SIGINT;
		ft_putstr_fd("\n", 1);
		return ;
	}
	else if (signum == SIGQUIT)
	{
		g_sig_handle = SIGQUIT;
		ft_putstr_fd("Quit (core dumped)\n", 2);
	}
}

void	signal_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_sig_handle = SIGINT;
		close(STDIN_FILENO);
	}
}

void	signal_loop(t_data	*data)
{
	(void) data;
	g_sig_handle = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, signal_handler);
}
