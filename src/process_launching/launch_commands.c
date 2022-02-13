//
// Created by sergey on 01.02.2022.
//

#include "../../includes/minishell.h"

static int is_built_in(t_list *cmd_lst)
{
	char *cmd_str;
	cmd_str = get_cmd_str(cmd_lst);
	if (!ft_strncmp(cmd_str, "pwd", ft_strlen(cmd_str)))
		return (1);
	if (!ft_strncmp(cmd_str, "env", ft_strlen(cmd_str)))
		return (1);
	if (!ft_strncmp(cmd_str, "exit", ft_strlen(cmd_str)))
		return (1);
	if (!ft_strncmp(cmd_str, "echo", ft_strlen(cmd_str)))
		return (1);
	if (!ft_strncmp(cmd_str, "cd", ft_strlen(cmd_str)))
		return (1);
	return (0);
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

	return (0);
}

int check_bin_path(char *path)
{
	if (access(path, X_OK) == 0)
	{
		return (BIN_SUCCEED);
	}
	return (BIN_PERM_ERR);
}

char *get_path(char *raw_cmd)
{
	char *path_env;
	char *full_path;
	char **x_paths;
	int status;

	path_env = get_env_var(g_env, "PATH=");
	x_paths = ft_split(path_env, ':');
	status = assemble_path(raw_cmd, x_paths, &full_path);
	free_str_arr(x_paths);
	if (status == BIN_SUCCEED)
		return (full_path);
	if (status == BIN_PERM_ERR)
		perror(raw_cmd);//printf("%s: Permission denied\n", raw_cmd);
	if (status == BIN_NOT_FOUND)
	{
		ft_put_err("minishell: ");
		ft_put_err(raw_cmd);//printf("%s: Command not found\n", raw_cmd);
		ft_put_err(": command not found\n");
	}
	if (status == BIN_IS_DIR)
	{
		ft_put_err("minishell: ");
		ft_put_err(raw_cmd);//printf("%s: Command not found\n", raw_cmd);
		ft_put_err(": is a directory\n");
	}
	exit(1);
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

int launch_simple(t_list *command_lst)
{
	int pid;

	pid = fork();
	if (!pid)
	{
		ft_exe(command_lst, command_lst);
	}
	wait(0);
	return (0);
}

int launch_commands(t_list **commands)
{
	int cmd_count;
	int std_io[2];
	int fd_to_close[2];
	int fd[2];
	t_list *command_lst = *commands;
	std_io[0] = dup(0);
	std_io[1] = dup(1);
	cmd_count = ft_lstsize(command_lst);

	if (cmd_count == 1 &&
		is_built_in(command_lst)){
		setup_fd(command_lst, std_io);
		launch_built_in(command_lst, command_lst);
	}
	else if (cmd_count == 1)
	{
		setup_fd(command_lst, std_io);
		launch_simple(command_lst);
	}
	else
	{
		while (command_lst)
		{

			if (command_lst->prev == NULL)
			{
				pipe(fd);
				dup2(fd[1], 1);
				close(fd[1]);
				if (!fork())
				{
					close(fd[0]);
					setup_fd(command_lst, std_io);
					ft_exe(command_lst, command_lst);
				}
			} else if (command_lst->prev != NULL && command_lst->next != NULL)
			{
				dup2(fd[0], 0);
				close(fd[0]);
				pipe(fd);
				dup2(fd[1], 1);
				close(fd[1]);
				if (!fork())
				{
					close(fd[0]);
					setup_fd(command_lst, std_io);
					ft_exe(command_lst, command_lst);
					if (is_built_in(command_lst)){
						ft_exit(0, NULL);
					}
				}
			} else
			{
				dup2(fd[0], 0);
				close(fd[0]);
				dup2(std_io[1], 1);
				if (!fork())
				{
					setup_fd(command_lst, std_io);
					ft_exe(command_lst, command_lst);
					if (is_built_in(command_lst)){
						ft_exit(0, NULL);
					}
				}
			}
			command_lst = command_lst->next;
		}
		while (cmd_count > 0)
		{
			wait(0);
			cmd_count--;
		}
	}
	dup2(std_io[0], 0);
	dup2(std_io[1], 1);
	return (0);
}

