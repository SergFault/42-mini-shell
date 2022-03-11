/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:37:26 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/11 22:26:18 by Sergey           ###   ########.fr       */
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

int	validate_wrds(t_list *l_cmds)
{
	while (l_cmds)
	{
		if (have_here_doc_cmds(l_cmds) && !have_lim_here_doc(l_cmds))
		{
			ft_put_err("syntax error near unexpected token `newline\'\n");
			return (0);
		}
		if (have_file_in_op(l_cmds) && !have_file_in(l_cmds))
		{
			ft_put_err("syntax error near unexpected token `newline\'\n");
			return (0);
		}
		if (have_any_out_redir_op(l_cmds) && !have_file_out(l_cmds))
		{
			ft_put_err("syntax error near unexpected token `newline\'\n");
			return (0);
		}
		l_cmds = l_cmds->next;
	}
	return (1);
}
