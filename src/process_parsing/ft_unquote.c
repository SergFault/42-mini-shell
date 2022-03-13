/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:35:57 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/12 13:39:13 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cpy_unquote(char *src, char *dst)
{
	int	quotes[2];
	int	i;
	int	j;

	i = 0;
	j = 0;
	quotes[1] = 0;
	quotes[0] = 0;
	while (src[i])
	{
		if (((src[i] == '\'') && quotes[1]) || ((src[i] == '\"') && quotes[0])
			|| ((src[i] != '\"') && (src[i] != '\'')))
		{
			change_quote_flags(quotes, src + i);
			dst[j] = src[i];
			i++;
			j++;
		}
		else
			change_quote_flags(quotes, src + i++);
	}
	dst[j] = '\0';
	return (0);
}

void	ft_unquote(char **str_p)
{
	size_t	len;
	char	*s;
	char	*result;

	s = *str_p;
	len = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * (len + 1));
	fatal_err_if(result == 0, NULL);
	result[len] = '\0';
	cpy_unquote(s, result);
	free(*str_p);
	*str_p = result;
}
