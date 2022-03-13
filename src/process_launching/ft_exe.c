/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 21:46:34 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/12 14:08:36 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

char	*get_path(char *raw_cmd, int *status)
{
	char	*path_env;
	char	*full_path;
	char	**x_paths;

	path_env = get_env_var(g_data.env, "PATH");
	if (!ft_strlen(path_env))
		x_paths = ft_split("./", ':');
	else
		x_paths = ft_split(path_env, ':');
	free(path_env);
	*status = assemble_path(raw_cmd, x_paths, &full_path);
	free_str_arr(x_paths);
	return (full_path);
}

int	launch_built_in(t_list *command, t_list *cmd_list)
{
	char	*cmd_str;
	int		ret_val;
	char	**argv;

	ret_val = 0;
	argv = get_args(command);
	cmd_str = get_word(get_cmd(command)->element)->val;
	if (ft_strnstr(cmd_str, "pwd", ft_strlen("pwd")))
		ret_val = ft_pwd();
	if (ft_strnstr(cmd_str, "env", ft_strlen("env")))
		ret_val = ft_env();
	if (ft_strnstr(cmd_str, "exit", ft_strlen("exit")))
		ret_val = ft_exit(argv, cmd_list);
	if (ft_strnstr(cmd_str, "echo", ft_strlen("echo")))
		ret_val = ft_echo(argv);
	if (ft_strnstr(cmd_str, "cd", ft_strlen("cd")))
		ret_val = ft_cd(argv);
	if (ft_strnstr(cmd_str, "export", ft_strlen("export")))
		ret_val = ft_export(argv);
	if (ft_strnstr(cmd_str, "unset", ft_strlen("unset")))
		ret_val = ft_unset(argv);
	free(argv);
	return (ret_val);
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
		ft_put_err_sh_cmd(get_word(get_cmd(command)->element)->val,
			"command not found");
		free_all_but_hist(cmds_to_free);
		exit(127);
	}
	else if (status == BIN_IS_DIR)
	{
		ft_put_err_sh_cmd(get_word(get_cmd(command)->element)->val,
			"Is a directory");
		free_all_but_hist(cmds_to_free);
		exit(126);
	}
	ft_put_err_sh_cmd(get_word(get_cmd(command)->element)->val,
		"No such file or directory");
	free_all_but_hist(cmds_to_free);
	exit(127);
}

static void	process_path(t_list *command, char **args, t_list *commands)
{
	char	*path;
	int		path_stat;

	path = get_path(get_word_by_type(command, ARG)->val, &path_stat);
	if (path_stat == BIN_PERM_ERR || path_stat == BIN_NOT_FOUND
		|| path_stat == BIN_IS_DIR || path_stat == FILE_NOT_FOUND)
	{
		free(args);
		free(path);
		process_bad_path(path_stat, command, commands);
	}
	execve(path, args, g_data.env);
}

int	ft_exe(t_list *command, t_list *commands)
{
	char	**args;

	args = get_args(command);
	if (is_built_in(command))
		return (launch_built_in(command, commands));
	if (args[0] == NULL)
	{
		free(args);
		free_all_but_hist(commands);
		exit(0);
	}
	else
	{
		process_path(command, args, commands);
	}
	return (0);
}
