/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:24:28 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/11 22:27:39 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

static void	init(t_list **commands, char **env)
{
	g_data.ret_val = 0;
	*commands = NULL;
	parse_environment(env);
}

static void	ft_read_line(char **input)
{
	hook_signals();
	*input = readline(PROMPT);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_list		*commands;

	if (argc > 1 && argv[0])
		exit(ft_put_err_simple("Error: arguments are not supported\n"));
	init(&commands, env);
	while (1)
	{
		ft_read_line(&input);
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
