/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consider_empty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 19:10:54 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/04 23:52:04 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_inconsiderable(char ch)
{
	if (ch == ' ' || ch == '\f' || ch == '\n'
		|| ch == '\r' || ch == '\t' || ch == '\v')
		return (1);
	else
		return (0);
}

int	consider_empty(char *str)
{
	while (*str)
	{
		if (!is_inconsiderable(*str))
			return (0);
		else
			str++;
	}
	return (1);
}
