/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:25:54 by eshana            #+#    #+#             */
/*   Updated: 2022/02/07 13:46:35 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*str;

	str = get_env_var(g_env, "PWD=");
	if (str)
	{
		printf("%s\n", str);
		return (0);
	}
	printf("fail\n");
	return (1);
}
