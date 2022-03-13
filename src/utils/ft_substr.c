/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:56:39 by sergey            #+#    #+#             */
/*   Updated: 2022/02/13 20:51:33 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	if (ft_strlen(s) == 0 || len == 0 || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) < (len + start))
		len = ft_strlen(s) - start;
	sub = malloc(sizeof(char) * (len + 1));
	fatal_err_if(!sub, NULL);
	while (j < len)
		sub[j++] = s[start + i++];
	sub[j] = '\0';
	return (sub);
}
