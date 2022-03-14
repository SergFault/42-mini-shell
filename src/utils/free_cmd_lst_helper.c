/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:53:24 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/13 13:41:04 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_but_hist(t_list *cmds)
{
	free_cmds(&cmds);
	free_str_arr(g_data.env);
}

void	free_all(t_list *cmds)
{
	rl_clear_history();
	free_cmds(&cmds);
	free_str_arr(g_data.env);
}

void	fatal_err_if(int bool, t_list *cmds)
{
	if (bool)
	{
		ft_put_err("Fatal error.\n");
		rl_clear_history();
		if (cmds)
			free_cmds(&cmds);
		free_str_arr(g_data.env);
		exit(2);
	}
}
