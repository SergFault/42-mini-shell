/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:25:39 by eshana            #+#    #+#             */
/*   Updated: 2022/02/28 15:20:40 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **argv)
{
	int	new_line;
	int	size;
	int	i;

	new_line = 1;
	i = 1;
	size = ft_str_arr_size(argv);
	if (size >= 2 && !ft_strcmp(argv[1], "-n"))
	{
		new_line = 0;
		i = 2;
	}
	while (argv[i])
	{
		printf("%s", argv[i++]);
		if (argv[i])
			printf(" ");
	}
	if (new_line)
		printf("\n");
	free(argv);
	return (0);
}
