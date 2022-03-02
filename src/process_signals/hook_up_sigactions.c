/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_up_sigactions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 19:38:42 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/02 19:46:39 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void sig_handler(int sig_no)
{
	if (sig_no == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}

	if (sig_no == SIGTERM){
		exit(g_status);
	}

	if (sig_no == SIGQUIT)
	{
		exit(g_status);
	}
}

void hook_signals()
{
	signal(SIGINT, sig_handler);
}
