/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:59:47 by sergey            #+#    #+#             */
/*   Updated: 2021/04/23 18:43:36 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && --n && s1[i] && s2[i])
		i++;
	if (s2[i] == '\0' && s1[i] == '\0')
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
