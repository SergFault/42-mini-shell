/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:54:37 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/07 21:55:06 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_arr(char **str_arr)
{
	char	**temp;

	temp = str_arr;
	while (*str_arr)
	{
		free(*str_arr);
		str_arr++;
	}
	free(temp);
}
