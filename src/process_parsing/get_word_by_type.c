/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word_by_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:39:07 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/07 21:39:30 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_word	*get_word_by_type(t_list *cmd, enum e_type t)
{
	t_command	*command;
	t_list		*word_lst;

	command = get_cmd(cmd);
	word_lst = command->element;
	while (word_lst)
	{
		if (get_word(word_lst)->t == t)
			return (get_word(word_lst));
		word_lst = word_lst->next;
	}
	return (NULL);
}
