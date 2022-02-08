/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:26:52 by sergey            #+#    #+#             */
/*   Updated: 2022/02/08 13:49:18 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst)
		return ;
	if (!*lst)
	{
		new->next = NULL;
		new->prev = NULL;
		*lst = new;
	}
	else
	{
		new->next = *lst;
		(*lst)->prev = new;
		*lst = new;
		new->prev = NULL;
	}
}
