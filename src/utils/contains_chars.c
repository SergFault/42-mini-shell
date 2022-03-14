/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contains_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:32:51 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/14 16:42:08 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str_cons_only_chars(char *str, char *str_ch)
{
	int	i;

	while (*str)
	{
		i = 0;
		while (1)
		{
			if (str_ch[i] == *str)
				break ;
			if (str_ch[i] == '\0')
				return (0);
			i++;
		}
		str++;
	}
	return (1);
}
