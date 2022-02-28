/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:24:28 by Sergey            #+#    #+#             */
/*   Updated: 2022/02/28 18:34:34 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**g_env;
int	g_status;

void	print_env(char **env)
{
	while (*env)
	{
		printf("%s", *env++);
		printf("\n");
	}
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_list		*commands;

	g_status = 0;
	commands = NULL;
	hook_signals();
	parse_environment(env);
	while (1)
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
		commands = parse_input(&input);
		launch_commands(&commands);
		delete_all_files();
		free_cmds(&commands);
		free(input);
		printf("%d\n", g_status);
	}
	free_all(commands);
}
