//
// Created by sergey on 01.02.2022.
//
#include "../includes/mini_shell.h"

char **g_env;

void print_env(char **env)
{
	while (*env)
	{
		printf("%s", *env++);
		printf("\n");
	}
}

void print_prompt(){

}

int main(int argc, char **argv, char **env)
{
	char *input;
	char **commands;

	hook_signals();
	parse_environment(env);
	while(1)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		if (consider_empty(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		commands = ft_split(input, ';');
		launch_commands(commands);
		free(input);
//		printf("\n");
//		print_env(env);
//		chdir("..");
//		print_env(env);
//	launch_commands();
	}
	return (0);
}