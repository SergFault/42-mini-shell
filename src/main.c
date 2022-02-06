
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
	t_list *commands;
	commands = NULL;

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
		commands = parse_input(input);
		launch_commands(&commands);
		free(input);
	}
	free_cmds(&commands);
	free_str_arr(g_env);
	return (0);
}