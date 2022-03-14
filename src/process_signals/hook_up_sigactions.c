/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_up_sigactions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 19:38:42 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/14 02:51:54 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

void	sig_handler2(int sig_no)
{
	if (sig_no == SIGINT)
	{
		g_data.ret_val = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else if (sig_no == SIGTERM)
		exit(130);
}

void	sig_handler(int sig_no)
{
	if (sig_no == SIGINT)
	{
		g_data.ret_val = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig_no == SIGTERM)
		exit(130);
}

void	hook_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
