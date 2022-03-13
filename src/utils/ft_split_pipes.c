/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:57:07 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/13 13:25:08 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_datasnaps(const char *str, char del)
{
	size_t	c;
	int		quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	c = 1;
	while (*str)
	{
		if (*str == del && !(quotes[0] || quotes[1]))
		{
			c++;
			change_quote_flags(quotes, str++);
		}
		else
		{
			while ((*str != del || (quotes[0] || quotes[1])) && *str)
				change_quote_flags(quotes, str++);
		}
	}
	return (c);
}

static void	skip_body(char del, const char **src, int *quotes, size_t *size)
{
	while ((**src != del || (quotes[0] || quotes[1])) && **src)
	{
		change_quote_flags(quotes, *src);
		(*src)++;
		(*size)++;
	}
}

static int	ft_parse(char **str, const char *src, char del, size_t d_snaps)
{
	size_t	size;
	size_t	str_n;
	int		quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	str_n = 0;
	while (str_n < d_snaps)
	{
		size = 0;
		if (*src == del && !(quotes[0] || quotes[1]))
			src++;
		skip_body(del, &src, quotes, &size);
		str[str_n] = (char *)malloc(sizeof(char) * (size + 1));
		fatal_err_if(!str[str_n], NULL);
		src -= size;
		ft_strlcpy(str[str_n], src, size + 1);
		src += size;
		str_n++;
	}
	return (1);
}

char	**ft_split_pipes(char const *s)
{
	char	**ret;
	size_t	data_snaps;

	if (!s)
		return (NULL);
	data_snaps = ft_datasnaps(s, '|');
	ret = (char **)malloc(sizeof(char *) * (data_snaps + 1));
	fatal_err_if(!ret, NULL);
	ft_parse(ret, s, '|', data_snaps);
	ret[data_snaps] = NULL;
	return (ret);
}
