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

char **get_args(t_list *command){

	t_list *iter;
	char **args;
	iter = get_cmd(command)->element;
	int args_count;
	int pos;

	args_count = 0;
	while (iter)
	{
		if (get_word(iter)->t == ARG)
			args_count++;
		iter = iter->next;
	}
	args = (char **)malloc(sizeof(char *) * (args_count + 1));
	iter = get_cmd(command)->element;
	pos = -1;
	while (iter){
//		if (get_word(iter)->t == ARG)
			args[++pos] = get_word(iter)->val;
		iter = iter->next;
	}
	args[++pos] = NULL;
	return args;
}

int ft_exe(t_list *command){

	char **args = get_args(command);
	int pos = -1;
//	while(*args[++pos]){
//		printf("%s\n", *args);
//	}
	execve(get_path(get_word(get_cmd(command)->element)->val) ,
		   args, g_env);
	free(args);
	return (0);
}

int launch_piped(t_list *command_lst){
	int std_in;
	int std_out;
	int fd[2];
	int pid;
	int pid1;

	std_in = dup(0);
	std_out = dup(1);

	while (command_lst->next)
	{
		pipe(fd);
		pid = fork();
		if (!pid) /* child */
		{
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
			ft_exe(command_lst->next);
		} else /* parent */
		{
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			pid1 = fork();
			if (!pid1)
			{
				ft_exe(command_lst);
			}
			wait(0);
			break;
		}
		command_lst = command_lst->next;
	}
	dup2(std_in, 0);
	dup2(std_out, 1);
	if (pid)
		wait(0);
	return (0);
}

int launch_simple(t_list *command_lst){
	int pid;

	pid = fork();
	if(!pid){
		ft_exe(command_lst);
	}
	wait(0);
	return (0);
}

int launch_commands(t_list **commands)
{
	t_list *command_lst = *commands;
	if (ft_lstsize(command_lst) > 1){
		launch_piped(command_lst);
	} else
	{
		launch_simple(command_lst);
	}

	return (0);
}

