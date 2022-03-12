/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:37:26 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/12 14:17:38 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_in(char *input)
{
	if (have_first_last_char(input, '|'))
	{
		ft_put_err("syntax error near unexpected token `|\'\n");
		return (0);
	}
	return (1);
}

static int	consider_cmd_fatal_empty(t_list *cmd)
{
	if (!get_word_by_type(cmd, ARG)
		&& !((get_word_by_type(cmd, FILE_IN_OP)
				|| get_word_by_type(cmd, FILE_OUT_APPEND_OP)
				|| get_word_by_type(cmd, FILE_OUT_OP)
				|| get_word_by_type(cmd, HERE_DOC_OP))))
		return (1);
	return (0);
}

int	validate_wrds(t_list *l_cmds)
{
	while (l_cmds)
	{
		if (consider_cmd_fatal_empty(l_cmds))
		{
			ft_put_err("syntax error near unexpected token `|\'\n");
			return (0);
		}
		if ((have_here_doc_cmds(l_cmds) && !have_lim_here_doc(l_cmds))
			|| (have_file_in_op(l_cmds) && !have_file_in(l_cmds))
			|| (have_any_out_redir_op(l_cmds) && !have_file_out(l_cmds)))
		{
			ft_put_err("syntax error near unexpected token `newline\'\n");
			return (0);
		}
		l_cmds = l_cmds->next;
	}
	return (1);
}
