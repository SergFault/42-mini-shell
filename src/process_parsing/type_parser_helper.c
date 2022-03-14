/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_parser_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:48:21 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/14 15:40:50 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_out_file(t_list *word)
{
	if (ft_str_cons_only_chars(((t_word *)(word->content))->val, "<>"))
		return (0);
	if ((word->prev) && (get_word_type(word->prev) == FILE_OUT_OP))
		return (1);
	return (0);
}

int	is_lim(t_list *word)
{
	if (ft_str_cons_only_chars(((t_word *)(word->content))->val, "<>"))
		return (0);
	if ((word->prev) && (get_word_type(word->prev) == HERE_DOC_OP))
		return (1);
	return (0);
}

int	is_in_file(t_list *word)
{
	if (ft_str_cons_only_chars(((t_word *)(word->content))->val, "<>"))
		return (0);
	if ((word->prev) && (get_word_type(word->prev) == FILE_IN_OP))
		return (1);
	return (0);
}

int	is_file_out_append_op(t_list *word)
{
	char	*str_word;

	str_word = get_word_str(word);
	if (!ft_strcmp(str_word, ">>"))
		return (1);
	return (0);
}

int	is_file_out_op(t_list *word)
{
	char	*str_word;

	str_word = get_word_str(word);
	if (!ft_strcmp(str_word, ">"))
		return (1);
	return (0);
}
