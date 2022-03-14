/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:34:36 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/14 17:43:02 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delim(char i)
{
	return (i == ' ' || i == '>' || i == '<');
}

t_list	*get_invalid_token(t_list *commands_list)
{
	t_list	*word_lst;

	word_lst = get_cmd(commands_list)->element;
	while (word_lst)
	{
		if (get_word(word_lst)->t == INVALID_TOKEN)
			return (word_lst);
		word_lst = word_lst->next;
	}
	return (NULL);
}

t_list	*file_op_without_file(t_list *commands_list)
{
	t_list	*word_lst;

	word_lst = get_cmd(commands_list)->element;
	while (word_lst)
	{
		if (get_word(word_lst)->t == FILE_OUT_APPEND_OP)
			if (!(word_lst->next) || get_word(word_lst->next)->t
				!= FILE_OUT_APPEND_OP)
				return (word_lst);
		if (get_word(word_lst)->t == FILE_OUT_OP)
			if (!(word_lst->next) || get_word(word_lst->next)->t != OUT_FILE)
				return (word_lst);
		if (get_word(word_lst)->t == FILE_IN_OP)
			if (!(word_lst->next) || get_word(word_lst->next)->t != IN_FILE)
				return (word_lst);
		word_lst = word_lst->next;
	}
	return (NULL);
}

t_list	*heredoc_without_delim(t_list *commands_list)
{
	t_list	*word_lst;

	word_lst = get_cmd(commands_list)->element;
	while (word_lst)
	{
		if (get_word(word_lst)->t == HERE_DOC_OP)
			if (!(word_lst->next) || get_word(word_lst->next)->t != LIM)
				return (word_lst);
		word_lst = word_lst->next;
	}
	return (NULL);
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
