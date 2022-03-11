/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:34:42 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/11 14:50:11 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_result(char *full_key, char *var_val)
{
	int	key_size;

	key_size = strlen(full_key);
	free(full_key);
	return (ft_strdup(var_val + key_size));
}

char	*get_env_var(char **var_arr, char *key)
{
	int		i;
	char	*var_val;
	char	*full_key;

	if (ft_strncmp(key, "?", 2) == 0)
	{
		var_val = ft_itoa(g_data.ret_val);
		return (var_val);
	}
	else
	{
		full_key = ft_strjoin(key, "=");
		i = 0;
		while (var_arr[i])
		{
			var_val = ft_strnstr(var_arr[i], full_key, ft_strlen(full_key));
			if (var_val)
				return (get_result(full_key, var_val));
			i++;
		}
		free(full_key);
		return (ft_strdup(""));
	}
}
