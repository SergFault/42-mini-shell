/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_forked.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:46:12 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/11 15:34:40 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_first(t_list *command_lst, int fd[2], int std_io[2])
{
	pipe(fd);
	dup2(fd[1], 1);
	close(fd[1]);
	if (!fork())
	{
		reset_signals();
		close(fd[0]);
		setup_fd(command_lst, std_io);
		ft_exe(command_lst, command_lst);
		if (is_built_in(command_lst))
		{
			exit(g_data.ret_val);
		}
	}
}

static void	pipe_mid(t_list *command_lst, int *fd, int std_io[2])
{
	dup2(fd[0], 0);
	close(fd[0]);
	pipe(fd);
	dup2(fd[1], 1);
	close(fd[1]);
	if (!fork())
	{
		reset_signals();
		close(fd[0]);
		setup_fd(command_lst, std_io);
		ft_exe(command_lst, command_lst);
		if (is_built_in(command_lst))
		{
			exit(g_data.ret_val);
		}
	}
}

static void	pipe_last(t_list *command_lst, int *fd, int std_io[2])
{
	dup2(fd[0], 0);
	close(fd[0]);
	dup2(std_io[1], 1);
	if (!fork())
	{
		reset_signals();
		setup_fd(command_lst, std_io);
		ft_exe(command_lst, command_lst);
		if (is_built_in(command_lst))
		{
			exit(g_data.ret_val);
		}
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}

void	launch_forked(t_list *command_lst, int fd[2], int std_io[2],
						int cmd_count)
{
	while (command_lst)
	{
		if (command_lst->prev == NULL)
			pipe_first(command_lst, fd, std_io);
		else if (command_lst->prev != NULL && command_lst->next != NULL)
			pipe_mid(command_lst, fd, std_io);
		else
			pipe_last(command_lst, fd, std_io);
		command_lst = command_lst->next;
	}
	while (cmd_count > 0)
	{
		ft_wait_status();
		cmd_count--;
	}
}
