/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_first_last_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:43:04 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/02 17:43:50 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_first_last_char(char *string, char ch)
{
	int	counter;

	counter = 0;
	if (string[0] == ch)
		return (1);
	while (string[counter + 1])
		counter++;
	if (string[counter] == ch)
		return (1);
	return (0);
}
