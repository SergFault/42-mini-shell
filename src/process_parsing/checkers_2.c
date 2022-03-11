/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:34:36 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/11 22:20:34 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_file_in_op(t_list *commands_list)
{
	t_list	*word_lst;

	word_lst = get_cmd(commands_list)->element;
	while (word_lst)
	{
		if (get_word(word_lst)->t == FILE_IN_OP)
			return (1);
		word_lst = word_lst->next;
	}
	return (0);
}

int	have_file_in(t_list *commands_list)
{
	t_list	*word_lst;

	word_lst = get_cmd(commands_list)->element;
	while (word_lst)
	{
		if (get_word(word_lst)->t == IN_FILE)
			return (1);
		word_lst = word_lst->next;
	}
	return (0);
}

int	have_any_out_redir_op(t_list *commands_list)
{
	t_list	*word_lst;

	word_lst = get_cmd(commands_list)->element;
	while (word_lst)
	{
		if ((get_word(word_lst)->t == FILE_OUT_APPEND_OP)
			|| (get_word(word_lst)->t == FILE_OUT_OP))
			return (1);
		word_lst = word_lst->next;
	}
	return (0);
}

int	have_file_out(t_list *commands_list)
{
	t_list	*word_lst;

	word_lst = get_cmd(commands_list)->element;
	while (word_lst)
	{
		if (get_word(word_lst)->t == OUT_FILE
			|| get_word(word_lst)->t == FILE_OUT_APPEND)
			return (1);
		word_lst = word_lst->next;
	}
	return (0);
}
