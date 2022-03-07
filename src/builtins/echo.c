/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:25:39 by eshana            #+#    #+#             */
/*   Updated: 2022/03/07 12:54:49 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_arg_is_flag(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_echo(char **argv)
{
	int	new_line;
	int	size;
	int	i;

	new_line = 1;
	i = 1;
	size = ft_str_arr_size(argv);
	while (argv[i] && ft_arg_is_flag(argv[i]))
	{
		i++;
		new_line = 0;
	}
	while (argv[i])
	{
		printf("%s", argv[i++]);
		if (argv[i])
			printf(" ");
	}
	if (new_line)
		printf("\n");
	return (0);
}
