/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_unexpected.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:23:40 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/14 17:39:12 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_token(t_list *invalid_word, t_list **un_token)
{
	if (!invalid_word->next)
	{
		*un_token = (NULL);
		return (1);
	}
	else
	{
		*un_token = invalid_word->next;
		return (1);
	}
}

int	catch_unexpected(t_list *cmd, t_list **un_token)
{
	t_list	*invalid_word;

	invalid_word = heredoc_without_delim(cmd);
	if (invalid_word)
		return (set_token(invalid_word, un_token));
	invalid_word = get_invalid_token(cmd);
	if (invalid_word)
		return (set_token(invalid_word, un_token));
	invalid_word = file_op_without_file(cmd);
	if (invalid_word)
		return (set_token(invalid_word, un_token));
	return (0);
}
