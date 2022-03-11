/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:24:28 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/07 23:02:34 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

static void	print_env(char **env)
{
	while (*env)
	{
		printf("%s", *env++);
		printf("\n");
	}
}

static void	arg_shot(char *arg_cmd)
{
	char	*input;
	t_list	*commands;

	input = ft_strdup(arg_cmd);
	commands = parse_input(&input);
	launch_commands(&commands);
	delete_all_files();
	free_cmds(&commands);
	free(input);
	exit(g_data.ret_val);
}

static void	init(t_list **commands, char **env)
{
	g_data.ret_val = 0;
	*commands = NULL;
	parse_environment(env);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_list		*commands;

	init(&commands, env);
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
		arg_shot(argv[2]);
	while (1)
	{
		hook_signals();
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
	}
	free_all(commands);
	return (g_data.ret_val);
}
