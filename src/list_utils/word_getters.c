/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_getters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:30:35 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/06 20:35:51 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_first_arg_word_str_ref(t_list *cmd)
{
	t_list *word_lst;

	word_lst = get_cmd(cmd)->element;
	while (word_lst)
	{
		if (((t_word *) word_lst->content)->t == ARG)
			return ((t_word *) word_lst->content)->val;
		word_lst = word_lst->next;
	}
	return (NULL);
}