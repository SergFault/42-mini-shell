/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:37:26 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/14 17:40:48 by Sergey           ###   ########.fr       */
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

void	print_unexpected_token(t_list *unexpected)
{
	const char	*token;

	if (!unexpected)
		token = "newline";
	else
		token = (((t_word *)(unexpected->content))->val);
	ft_put_err("syntax error near unexpected token `");
	ft_put_err_simple(token);
	ft_put_err_simple("'\n");
}

int	validate_wrds(t_list *l_cmds)
{
	t_list	*unexpected_token;

	while (l_cmds)
	{
		if (consider_cmd_fatal_empty(l_cmds))
		{
			ft_put_err("syntax error near unexpected token `|\'\n");
			return (0);
		}
		if (catch_unexpected(l_cmds, &unexpected_token))
		{
			print_unexpected_token(unexpected_token);
			return (0);
		}
		l_cmds = l_cmds->next;
	}
	return (1);
}
