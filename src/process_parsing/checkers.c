/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:34:36 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/11 22:27:02 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delim(char i)
{
	return (i == ' ' || i == '>' || i == '<');
}

int	have_here_doc_cmds(t_list *commands_list)
{
	t_list	*word_lst;

	word_lst = get_cmd(commands_list)->element;
	while (word_lst)
	{
		if (get_word(word_lst)->t == HERE_DOC_OP)
			return (1);
		word_lst = word_lst->next;
	}
	return (0);
}

int	have_lim_here_doc(t_list *commands_list)
{
	t_list	*word_lst;

	word_lst = get_cmd(commands_list)->element;
	while (word_lst)
	{
		if (get_word(word_lst)->t == LIM)
			return (1);
		word_lst = word_lst->next;
	}
	return (0);
}
