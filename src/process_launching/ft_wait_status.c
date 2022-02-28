/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:29:28 by Sergey            #+#    #+#             */
/*   Updated: 2022/02/28 19:34:26 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	ft_wait_status(void)
{
	int	stat_loc;

	stat_loc = 0;
	wait(&stat_loc);
	g_status = WEXITSTATUS(stat_loc);
}
