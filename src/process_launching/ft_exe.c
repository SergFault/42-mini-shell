/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 21:46:34 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/02 14:42:28 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

char	*get_path(char *raw_cmd, int *status)
{
	char	*path_env;
	char	*full_path;
	char	**x_paths;

	path_env = get_env_var(g_env, "PATH");
	x_paths = ft_split(path_env, ':');
	free(path_env);
	*status = assemble_path(raw_cmd, x_paths, &full_path);
	free_str_arr(x_paths);
	return (full_path);
}

int	launch_built_in(t_list *command, t_list *cmd_list)
{
	char	*cmd_str;

	cmd_str = get_word(get_cmd(command)->element)->val;
	if (ft_strnstr(cmd_str, "pwd", ft_strlen("pwd")))
		ft_pwd();
	if (ft_strnstr(cmd_str, "env", ft_strlen("env")))
		ft_env();
	if (ft_strnstr(cmd_str, "exit", ft_strlen("exit")))
		ft_exit(get_args(command), cmd_list);
	if (ft_strnstr(cmd_str, "echo", ft_strlen("echo")))
		ft_echo(get_args(command));
	if (ft_strnstr(cmd_str, "cd", ft_strlen("cd")))
		ft_cd(get_args(command));
	if (ft_strnstr(cmd_str, "export", ft_strlen("export")))
		ft_export(get_args(command));
	return (0);
}

void	process_bad_path(int status, t_list *command, t_list *cmds_to_free)
{
	if (status == BIN_PERM_ERR)
	{
		ft_put_err_sh_cmd(get_word(get_cmd(command)->element)->val,
			"Permission denied");
		free_all_but_hist(cmds_to_free);
		exit(126);
	}
	else if (status == BIN_NOT_FOUND)
	{
		ft_put_err_cmd(get_word(get_cmd(command)->element)->val,
			"command not found");
		free_all_but_hist(cmds_to_free);
		exit(127);
	}
	else if (status == BIN_IS_DIR)
	{
		ft_put_err_cmd(get_word(get_cmd(command)->element)->val,
			"Is a directory");
		free_all_but_hist(cmds_to_free);
		exit(126);
	}
}

int	ft_exe(t_list *command, t_list *commands)
{
	char	**args;
	int		path_stat;
	char	*path;

	path_stat = 0;
	args = get_args(command);
	if (is_built_in(command))
	{
		launch_built_in(command, commands);
	}
	else
	{
		path = get_path(get_word(get_cmd(command)->element)->val, &path_stat);
		if (path_stat == BIN_PERM_ERR || path_stat == BIN_NOT_FOUND
			|| path_stat == BIN_IS_DIR)
		{
			free(args);
			free(path);
			process_bad_path(path_stat, command, commands);
		}
		execve(path, args, g_env);
	}
}
