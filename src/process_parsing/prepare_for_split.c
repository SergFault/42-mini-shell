//
// Created by sergey on 13.02.2022.
//

#include "minishell.h"

void ft_substitution(char **str_p)
{
	char *str;
	int pos;
	char *var;
	char *var_val;
	char **splitted;
	char *result;
	char *temp;
	int quotes[2];

	quotes[1] = 0;
	quotes[0] = 0;
	str = *str_p;
	pos = 0;
	result = NULL;
	while (str[pos])
	{
		if (str[pos] == '$' && !quotes[0])
		{
			if (quotes[1])
				splitted = ft_split(str + (pos) + 1, '\"');
			else
				splitted = ft_split_spaces(str + (pos) + 1);
			var = splitted[0];
			str[pos] = '\0';
			temp = result;
			var_val = get_env_var(g_env, var);
			result = ft_strjoin(str, var_val);
			if (temp)
				free(temp);
			temp = result;
			result = ft_strjoin(result, str + (pos + ft_strlen(var) + 1));
			free(temp);
			temp = str;
			str = result;
			free(temp);
			temp = NULL;
			free_str_arr(splitted);
			free(var_val);
			pos = 0;
		}
		if (!str[pos])
			break;
		change_quote_flags(quotes, str + pos);
		pos++;
	}
	*str_p = str;
}