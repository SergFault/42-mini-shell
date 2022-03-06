/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_for_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 19:12:36 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/06 19:11:50 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	needs_sub(char *str, int pos)
{
	if (strlen(str) == 1)
		return (0);
	if (pos != 0 && is_inconsiderable(str[pos + 1]))
		return (0);
	return (1);
}

void	make_substitution(char **str, int pos, char **splitted)
{
	char	*var;
	char	*temp;
	char	*result;
	char	*var_val;

	var = splitted[0];
	(*str)[pos] = '\0';
	var_val = get_env_var(g_data.env, var);
	result = ft_strjoin(*str, var_val);
	temp = result;
	result = ft_strjoin(result, *str + (pos + ft_strlen(var) + 1));
	free(temp);
	temp = *str;
	*str = result;
	free(temp);
	temp = NULL;
	free_str_arr(splitted);
	free(var_val);
}

static char	**resolve_split(int quotes[2], char *str, int pos)
{
	if (!quotes[0] && (str + pos + 1) == '?')
	{
		char **ret_val = (char **) malloc(sizeof(char *) * 2);
		ret_val[0] = ft_strdup("?");
		ret_val[1] = NULL;
		return ret_val;
	}
	if (quotes[1])
		return (ft_split_multiple_del(str + (pos) + 1, "\'\" \f\n\r\t\v"));
	else
		return (ft_split_multiple_del(str + (pos) + 1, "$ \'\" \f\n\r\t\v"));
}

void	ft_substitution(char **str_p)
{
	char	*str;
	int		pos;
	char	**splitted;
	int		quotes[2];

	quotes[1] = 0;
	quotes[0] = 0;
	str = *str_p;
	pos = 0;
	while (str[pos])
	{
		if (str[pos] == '$' && !quotes[0] && needs_sub(str, pos))
		{
			splitted = resolve_split(quotes, str, pos);
			make_substitution(&str, pos, splitted);
			continue ;
		}
		if (!str[pos])
			break ;
		change_quote_flags(quotes, str + pos);
		pos++;
	}
	*str_p = str;
}
