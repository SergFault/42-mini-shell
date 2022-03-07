/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:25:54 by eshana            #+#    #+#             */
/*   Updated: 2022/02/08 23:29:51 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*str;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * (PATH_MAX + 1));
	if (!buf)
	{
		perror("minitalk: ");
		return (errno);
	}
	str = getcwd(buf, PATH_MAX);
	if (str)
	{
		printf("%s\n", str);
		free(buf);
		return (0);
	}
	free(buf);
	return (1);
}
