/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_up_sigactions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 19:38:42 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/07 12:54:34 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

void	sig_handler(int sig_no)
{
	g_data.ret_val = 1;
	if (sig_no == SIGINT)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig_no == SIGTERM)
		exit(g_data.ret_val);
	else if (sig_no == SIGQUIT)
		exit(g_data.ret_val);
}

void	sig_handler_fork(int sig_no)
{
	g_data.ret_val = sig_no + 128;
	if (sig_no == SIGINT)
		exit(g_data.ret_val);
	else if (sig_no == SIGTERM)
		exit(g_data.ret_val);
	else if (sig_no == SIGQUIT)
		exit(g_data.ret_val);
	exit(g_data.ret_val);
}

void	hook_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	hook_signals_fork(void)
{
	signal(SIGINT, sig_handler_fork);
	signal(SIGQUIT, SIG_DFL);
}
