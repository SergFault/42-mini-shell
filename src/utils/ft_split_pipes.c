/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:57:07 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/07 22:28:25 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_fail(char **str_a, int c)
{
	int	counter;

	counter = 0;
	while (counter < c)
	{
		free(str_a[c]);
		counter++;
	}
	return (0);
}

static size_t	ft_datasnaps(const char *str, char del)
{
	size_t	c;
	int		quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	c = 0;
	while (*str)
	{
		if (*str == del && !(quotes[0] || quotes[1]))
		{
			while (*str == del && *str && !(quotes[0] || quotes[1]))
				change_quote_flags(quotes, str++);
		}
		else
		{
			c++;
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
		while (*src == del && !(quotes[0] || quotes[1]))
			src++;
		skip_body(del, &src, quotes, &size);
		str[str_n] = (char *)malloc(sizeof(char) * (size + 1));
		if (!(str[str_n]))
			return (free_fail(str, str_n));
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
	if (!(ret))
		return (NULL);
	ft_parse(ret, s, '|', data_snaps);
	ret[data_snaps] = NULL;
	return (ret);
}
