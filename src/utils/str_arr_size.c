//
// Created by sergey on 03.02.2022.
//

#include "../../includes/mini_shell.h"


int	ft_str_arr_size(char **str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}