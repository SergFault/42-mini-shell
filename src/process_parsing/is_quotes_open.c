/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quotes_open.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:07:21 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/04 23:52:04 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_quote_flags(int q_flags[2], const char *ch)
{
	if ((*ch == '\'') && (!q_flags[0]) && (!q_flags[1]))
		q_flags[0] = 1;
	else if ((*ch == '\"') && (!q_flags[0]) && (!q_flags[1]))
		q_flags[1] = 1;
	else if ((*ch == '\'') && (q_flags[0]))
		q_flags[0] = 0;
	else if ((*ch == '\"') && (q_flags[1]))
		q_flags[1] = 0;
}

int	is_quotes_open(char *str)
{
	int	in_quotes[2];

	in_quotes[0] = 0;
	in_quotes[1] = 0;
	if (!str)
		return (0);
	while (*str)
	{
		change_quote_flags(in_quotes, str);
		str++;
	}
	return (in_quotes[0] || in_quotes[1]);
}

int	is_quotes(const char *str)
{
	while (*str)
	{
		if (((*str) == '\'') || (*str) == '\"')
			return (1);
		(str++);
	}
	return (0);
}
