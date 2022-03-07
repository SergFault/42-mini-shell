/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:32:07 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/07 22:32:07 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	counter;

	if (!dst || !src)
		return (0);
	counter = ft_strlen(src);
	if (!size)
		return (counter);
	while (((size--) > 1) && (*src))
		*(dst++) = *(src++);
	*dst = '\0';
	return (counter);
}
