/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 21:46:34 by Sergey            #+#    #+#             */
/*   Updated: 2022/02/28 22:04:39 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

char	*get_path(char *raw_cmd)
{
	char	*path_env;
	char	*full_path;
	char	**x_paths;
	int		status;

	path_env = get_env_var(g_env, "PATH");
	x_paths = ft_split(path_env, ':');
	free(path_env);
	status = assemble_path(raw_cmd, x_paths, &full_path);
	free_str_arr(x_paths);
	if (status == BIN_SUCCEED)
		return (full_path);
	if (status == BIN_PERM_ERR)
		perror(raw_cmd);//printf("%s: Permission denied\n", raw_cmd);
	if (status == BIN_NOT_FOUND)
	{
		ft_put_err(raw_cmd);
		g_status = 2;
		ft_put_err(": command not found\n");
	}
	if (status == BIN_IS_DIR)
	{
		ft_put_err("minishell: ");
		ft_put_err(raw_cmd);//printf("%s: Command not found\n", raw_cmd);
		ft_put_err(": Is a directory\n");
	}
	exit(1);
}

int launch_built_in(t_list *command, t_list *cmd_list)
{
	char *cmd_str;

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

int ft_exe(t_list *command, t_list *commands)
{
	char **args;

	args = get_args(command);
	if (is_built_in(command))
	{
		launch_built_in(command, commands);
	} else
	{
		execve(get_path(get_word(get_cmd(command)->element)->val),
			   args, g_env);
	}
}