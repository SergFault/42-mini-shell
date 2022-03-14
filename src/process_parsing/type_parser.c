/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:45:44 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/14 16:47:02 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_file_out_append(t_list *word)
{
	if (ft_str_cons_only_chars(((t_word *)(word->content))->val, "<>"))
		return (0);
	if ((word->prev) && (get_word_type(word->prev) == FILE_OUT_APPEND_OP))
		return (1);
	return (0);
}

int	is_here_doc(t_list *word)
{
	char	*str_word;

	str_word = get_word_str(word);
	if (!ft_strcmp(str_word, "<<"))
		return (1);
	return (0);
}

int	is_invalid(t_list *word)
{
	char	*str_word;

	str_word = get_word_str(word);
	if (ft_strncmp(str_word, "<", 2) == 0
		|| ft_strncmp(str_word, "<<", 3) == 0
		|| ft_strncmp(str_word, ">", 2) == 0
		|| ft_strncmp(str_word, ">>", 3) == 0)
		return (0);
	if (str_word[0] == '<' || str_word[0] == '>')
		return (1);
	return (0);
}

int	is_file_in_op(t_list *word)
{
	char	*str_word;

	str_word = get_word_str(word);
	if (!ft_strcmp(str_word, "<"))
		return (1);
	return (0);
}

int	set_types(t_list *elements)
{
	while (elements)
	{
		if (is_invalid(elements))
			get_word(elements)->t = INVALID_TOKEN;
		else if (is_file_in_op(elements))
			get_word(elements)->t = FILE_IN_OP;
		else if (is_here_doc(elements))
			get_word(elements)->t = HERE_DOC_OP;
		else if (is_file_out_op(elements))
			get_word(elements)->t = FILE_OUT_OP;
		else if (is_file_out_append_op(elements))
			get_word(elements)->t = FILE_OUT_APPEND_OP;
		else if (is_in_file(elements))
			get_word(elements)->t = IN_FILE;
		else if (is_lim(elements))
			get_word(elements)->t = LIM;
		else if (is_out_file(elements))
			get_word(elements)->t = OUT_FILE;
		else if (is_file_out_append(elements))
			get_word(elements)->t = FILE_OUT_APPEND;
		else
			get_word(elements)->t = ARG;
		elements = elements->next;
	}
	return (0);
}
