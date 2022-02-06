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

int launch_built_in(t_list *command, t_list *cmd_list)
{
	char *cmd_str = get_word(get_cmd(command)->element)->val;
	if (ft_strnstr(cmd_str, "pwd", strlen("pwd")))
		ft_pwd();
	if (ft_strnstr(cmd_str, "env", strlen("env")))
		ft_env();
	if (ft_strnstr(cmd_str, "exit", strlen("exit")))
		ft_exit(get_args(command), cmd_list);
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
	int pos = -1;
}

int ft_exe(t_list *command, t_list *commands)
{
	int pid;
	char **args = get_args(command);

	char *cmd_str = get_word(get_cmd(command)->element)->val;
	if (is_built_in(cmd_str))
	{
		launch_built_in(command, commands);
	} else
	{
		execve(get_path(get_word(get_cmd(command)->element)->val),
				   args, g_env);
	}
	exit(0);
}


int launch_piped(t_list *command_lst)
{
	int cmd_count;
	int std_in;
	int std_out;
	int fd[2];
	std_in = dup(0);
	std_out = dup(1);

	cmd_count = ft_lstsize(command_lst);

	while (command_lst)
	{

		if (command_lst->prev == NULL){
			pipe(fd);
			dup2(fd[1], 1);
			close(fd[1]);
			if (!fork()){
				close(fd[0]);
				ft_exe(command_lst, command_lst);
			}
		}
		else if (command_lst->prev != NULL && command_lst->next != NULL)
		{
			dup2(fd[0], 0);
			close(fd[0]);
			pipe(fd);
			dup2(fd[1], 1);
			close(fd[1]);
			if (!fork()){
				close(fd[0]);
				ft_exe(command_lst, command_lst);
			}
		}
		else
		{
			dup2(fd[0], 0);
			close(fd[0]);
			dup2(std_out, 1);
			if (!fork()){
				ft_exe(command_lst, command_lst);
			}
		}
		command_lst = command_lst->next;
	}
	while(cmd_count > 0){
		wait(0);
		cmd_count--;
	}
	dup2(std_in, 0);
	dup2(std_out, 1);
	return (0);
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
	t_list *command_lst = *commands;
	if (ft_lstsize(command_lst) == 1 &&
		is_built_in(get_word(get_cmd(command_lst)->element)->val)){
		launch_built_in(command_lst, command_lst);
	}
	else if (ft_lstsize(command_lst) > 1)
	{
		launch_piped(command_lst);
	} else
	{
		launch_simple(command_lst);
	}

	return (0);
}

