/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:29:28 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/11 20:54:23 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

void	ft_wait_status(void)
{
	int	stat_loc;

	signal(SIGINT, sig_handler2);
	stat_loc = 0;
	wait(&stat_loc);
	g_data.ret_val = stat_loc;
	if (WIFEXITED(g_data.ret_val))
		g_data.ret_val = WEXITSTATUS(g_data.ret_val);
	else if (WIFSIGNALED(g_data.ret_val))
		g_data.ret_val = 128 + WTERMSIG(g_data.ret_val);
	signal(SIGINT, sig_handler);
}
