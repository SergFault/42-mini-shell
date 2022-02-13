//
// Created by sergey on 13.02.2022.
//

#include "minishell.h"

char *str_insert(char *big, char *pos, char *lit)
{
	char *str1;
	char *str3;
	char *temp;

	str3 = ft_strdup(pos);
	*pos = '\0';
	str1 = ft_strdup(big);
	temp = str1;
	str1 = ft_strjoin(str1, lit);
	free(temp);
	temp = str1;
	str1 = ft_strjoin(str1, str3);
	free(temp);
	free(big);
	return (str1);
}