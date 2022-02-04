/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:25:54 by eshana            #+#    #+#             */
/*   Updated: 2022/02/04 10:32:44 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_pwd(void)
{
	char	*str;
	size_t	i;

	i = 0;
	while (g_env[i])
	{
		str = ft_strnstr(g_env[i], "PWD=", 4);
		if (str)
		{
			printf("%s\n", str + 4);
			exit(0);
		}
		i++;
	}
	printf("fail\n");
	exit(1);
}
