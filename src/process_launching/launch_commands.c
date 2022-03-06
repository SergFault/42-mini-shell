/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:46:56 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/02 14:47:52 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	is_built_in(t_list *cmd_lst)
{
	char	*cmd_str;

	cmd_str = get_word(get_cmd(cmd_lst)->element)->val;
	if (!ft_strcmp(cmd_str, "pwd"))
		return (1);
	if (!ft_strcmp(cmd_str, "env"))
		return (1);
	if (!ft_strcmp(cmd_str, "exit"))
		return (1);
	if (!ft_strcmp(cmd_str, "echo"))
		return (1);
	if (!ft_strcmp(cmd_str, "cd"))
		return (1);
	if (!ft_strcmp(cmd_str, "export"))
		return (1);
	if (!ft_strcmp(cmd_str, "unset"))
		return (1);
	return (0);
}

int	check_bin_path(char *path)
{
	if (access(path, X_OK) == 0)
		return (BIN_SUCCEED);
	return (BIN_PERM_ERR);
}

int	launch_simple(t_list *command_lst)
{
	int	pid;

	pid = fork();
	if (!pid)
		ft_exe(command_lst, command_lst);
	ft_wait_status();
	return (0);
}

int	launch_commands(t_list **commands)
{
	int		cmd_count;
	int		std_io[2];
	int		fd[2];
	t_list	*command_lst;

	command_lst = *commands;
	std_io[0] = dup(0);
	std_io[1] = dup(1);
	cmd_count = ft_lstsize(command_lst);
	if (cmd_count == 1 && is_built_in(command_lst))
	{
		setup_fd(command_lst, std_io);
		launch_built_in(command_lst, command_lst);
	}
	else if (cmd_count == 1)
	{
		setup_fd(command_lst, std_io);
		launch_simple(command_lst);
	}
	else
		launch_forked(command_lst, fd, std_io, cmd_count);
	dup2(std_io[0], 0);
	dup2(std_io[1], 1);
	return (0);
}
