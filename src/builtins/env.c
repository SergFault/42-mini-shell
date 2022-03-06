/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:23:39 by eshana            #+#    #+#             */
/*   Updated: 2022/03/06 14:01:00 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(void)
{
	size_t	i;

	i = 0;
	while (g_data.env[i])
	{
		if (ft_strchr(g_data.env[i], '='))
			printf("%s\n", g_data.env[i]);
		i++;
	}
	return (0);
}
