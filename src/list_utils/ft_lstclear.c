/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 23:18:09 by sergey            #+#    #+#             */
/*   Updated: 2021/04/27 13:21:31 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*iter;
	t_list	*todel;

	if (!lst || !*lst)
		return ;
	iter = *lst;
	while (iter)
	{
		todel = iter;
		iter = iter->next;
		if (del)
			del(todel->content);
		free(todel);
	}
	*lst = 0;
}
