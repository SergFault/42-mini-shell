//
// Created by sergey on 01.02.2022.
//

#include "../../includes/mini_shell.h"

static int	is_built_in(const char *cmd)
{
	if (ft_strnstr(cmd, "pwd", 3))
		return (1);
	return (0);
}

int launch_built_in(char *raw_command, char *const args[])
{
	pid_t pid;
	char **cmd;

	cmd = ft_split_spaces(raw_command);
	pid = fork();
	if (pid == 0)
	{
		ft_pwd();
		//execve(cmd[0], cmd, g_env);
	}
	if (pid == -1){
		printf("Fork process error.\n");
		return (-1);
	}
	wait(&pid);
	free(cmd);
	return (0);
}

int launch_bin(char *raw_command, char *const args[])
{
	pid_t pid;
	char **cmd;

	cmd = ft_split_spaces(raw_command);
	pid = fork();
	if (pid == 0)
	{
		execve(cmd[0], cmd, g_env);
	}
	if (pid == -1){
		printf("Fork process error.\n");
		return (-1);
	}
	wait(&pid);
	free(cmd);
	return (0);
}

int launch_commands(char **raw_commands){

	int counter;
	counter = -1;
	while (raw_commands && raw_commands[++counter])
	{
		if (is_built_in(*raw_commands))
		{
			if (ft_strnstr(*raw_commands, "pwd", 3))
				launch_built_in(ft_strdup(raw_commands[0]), raw_commands);

//			launch_built_in(0);
		} else{
			launch_bin(ft_strdup(raw_commands[0]), raw_commands);
		}
	}
	return (0);
}

