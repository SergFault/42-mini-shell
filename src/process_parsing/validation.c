/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:37:26 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/07 15:02:49 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate(t_list *command_lst, char *input)
{
	if (have_empty_cmds(command_lst) || have_first_last_char(input, '|'))
	{
		ft_put_err("syntax error near unexpected token `|\'\n");
		return (0);
	}
	else if (have_here_doc_cmds(command_lst) && !have_lim_here_doc(command_lst))
	{
		ft_put_err("syntax error near unexpected token `newline\'\n");
		return (0);
	}
	return (1);
}
