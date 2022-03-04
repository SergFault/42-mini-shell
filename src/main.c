/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:24:28 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/03 15:16:25 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env;
int		g_status;

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
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		input = ft_strdup(argv[2]);
		commands = parse_input(&input);
		launch_commands(&commands);
		delete_all_files();
		free_cmds(&commands);
		free(input);
		exit(g_status);
	}
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
		//printf("%d\n", g_status); // todo debug only

	}
	free_all(commands);
	return (g_status);
}
