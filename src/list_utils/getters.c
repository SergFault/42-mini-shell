/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:08:23 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/12 14:06:36 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*get_cmd(t_list *lst)
{
	if (lst)
		return (lst->content);
	else
		return (NULL);
}

t_word	*get_word(t_list *lst)
{
	if (lst)
		return (lst->content);
	else
		return (NULL);
}

char	*get_word_str(t_list *lst)
{
	if (lst)
		return (((t_word *)(lst->content))->val);
	else
		return (NULL);
}

enum e_type	get_word_type(t_list *lst)
{
	if (lst)
		return (((t_word *)(lst->content))->t);
	else
		return (NONE);
}

char	**get_args(t_list *command)
{
	t_list	*iter;
	char	**args;
	int		args_count;
	int		pos;

	iter = get_cmd(command)->element;
	args_count = 0;
	while (iter)
	{
		if (get_word(iter)->t == ARG)
			args_count++;
		iter = iter->next;
	}
	args = (char **) malloc(sizeof(char *) * (args_count + 1));
	fatal_err_if(args == 0, NULL);
	iter = get_cmd(command)->element;
	pos = -1;
	while (iter)
	{
		if (get_word(iter)->t == ARG)
			args[++pos] = get_word(iter)->val;
		iter = iter->next;
	}
	args[++pos] = NULL;
	return (args);
}
