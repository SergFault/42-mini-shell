//
// Created by sergey on 01.02.2022.
//

#include "../../includes/mini_shell.h"

static int is_built_in(const char *cmd)
{
	if (ft_strnstr(cmd, "pwd", 3))
		return (1);
	if (ft_strnstr(cmd, "env", 3))
		return (1);
	if (ft_strnstr(cmd, "exit", 4))
		return (1);
	return (0);
}

int launch_built_in(char *raw_command, char *const args[])
{
	pid_t pid;
	char **cmd;

	cmd = ft_split_spaces(raw_command);

	if (ft_strnstr(cmd[0], "pwd", 3))
		ft_pwd();
	if (ft_strnstr(cmd[0], "env", 3))
		ft_env();
	if (ft_strnstr(cmd[0], "exit", 4))
		ft_exit();
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
	if (status == BIN_SUCCEED)
		return (full_path);
	if (status == BIN_PERM_ERR)
		printf("%s: Permission denied\n", raw_cmd);
	if (status == BIN_NOT_FOUND)
		printf("%s: Command not found\n", raw_cmd);
	exit(1);
}

int launch_bin(char *raw_command, char *const args[])
{
	pid_t pid;
	char **cmd;
	char *bin_path;

	cmd = ft_split_spaces(raw_command);
	if (is_built_in(cmd[0]))
	{
		launch_built_in(cmd[0], cmd);
	} else
	{
		pid = fork();
		if (pid == 0)
		{
			bin_path = get_path(cmd[0]);
//		printf(bin_path);
			execve(bin_path, cmd, g_env);
		}
		if (pid == -1)
		{
			printf("Fork process error.\n");
			return (-1);
		}
		wait(&pid);
	}
//		free(cmd);
	return (0);
}

int launch_commands(char **raw_commands)
{

	int counter;
	counter = -1;
	while (raw_commands && raw_commands[++counter])
	{
		launch_bin(raw_commands[0], raw_commands);
	}
	return (0);
}

