//
// Created by sergey on 01.02.2022.
//
#include "../includes/mini_shell.h"

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

	hook_signals();
	while(1)
	{
		input = readline(PROMPT);
		if (!input){
			free(input);
			ft_exit();
		}
		free(input);
		add_history(input);
			printf("%s\n", input);
		free(input);
//		printf("\n");
//		print_env(env);
//		chdir("..");
//		print_env(env);
//	launch_commands();
	}
}