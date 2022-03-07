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

extern t_data 	g_data;

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
		exit(g_data.ret_val);
	else if (sig_no == SIGQUIT)
		exit(g_data.ret_val);
}

void	hook_signals(void)
{
	signal(SIGINT, sig_handler);
}
