/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:14:20 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/04 23:52:04 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

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
		ft_put_err("syntax error: quotes");
		g_status = 2;
		return (NULL);
	}
	lines = ft_split_pipes(input);
	command_lst = map_lines_cmds(lines);
	if (have_empty_cmds(command_lst) || have_first_last_char(*input_p, '|'))
	{
		ft_put_err("syntax error near unexpected token `|\'");
		free_cmds(&command_lst);
		free(lines);
		g_status = 2;
		return (NULL);
	}
	free(lines);
	fill_words(command_lst);
	return (command_lst);
}
