/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:14:20 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/07 18:11:18 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

t_list	*map_lines_cmds(char **lines)
{
	int			pos;
	t_command	*cmd;
	t_list		*cmd_lst;

	cmd_lst = NULL;
	pos = -1;
	while (lines[++pos])
	{
		cmd = malloc(sizeof(t_command));
		cmd->cmd_line = lines[pos];
		cmd->element = NULL;
		ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
	}
	return (cmd_lst);
}

t_list	*parse_input(char **input_p)
{
	t_list	*command_lst;
	char	**lines;
	char	*input;

	input = *input_p;
	command_lst = NULL;
	if (is_quotes_open(input))
	{
		ft_put_err("syntax error: quotes\n");
		g_data.ret_val = 2;
		return (NULL);
	}
	lines = ft_split_pipes(input);
	command_lst = map_lines_cmds(lines);
	free(lines);
	fill_words(command_lst);
	if (validate(command_lst, input) == 0)
	{
		free_cmds(&command_lst);
		g_data.ret_val = 2;
		return (NULL);
	}
	return (command_lst);
}
