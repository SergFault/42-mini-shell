//
// Created by sergey on 03.02.2022.
//
#include "../../includes/mini_shell.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!(dup))
		return (0);
	ft_strlcpy(dup, s, (len + 1));
	return (dup);
}