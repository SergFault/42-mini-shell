/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_up_sigactions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 19:38:42 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/04 23:52:04 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	sig_handler(int sig_no)
{
	if (sig_no == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig_no == SIGTERM)
		exit(g_status);
	else if (sig_no == SIGQUIT)
		exit(g_status);
}

void	hook_signals(void)
{
	signal(SIGINT, sig_handler);
}
