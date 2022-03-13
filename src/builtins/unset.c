/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:26:10 by eshana            #+#    #+#             */
/*   Updated: 2022/03/11 14:12:11 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_new_env(char **new_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (g_data.env[j])
	{
		if (g_data.env[j][0])
			new_env[i++] = g_data.env[j++];
		else
			j++;
	}
}

static void	ft_delete_key(char *key)
{
	int		i;
	char	**new_env;

	i = 0;
	while (g_data.env[i])
	{
		if (!ft_keycmp(g_data.env[i], key))
		{
			g_data.env[i][0] = '\0';
			new_env = (char **)malloc(sizeof(char *)
					* ft_str_arr_size(g_data.env));
			fatal_err_if(new_env == 0, NULL);
			new_env[ft_str_arr_size(g_data.env) - 1] = NULL;
			ft_new_env(new_env);
			free(g_data.env);
			g_data.env = new_env;
			return ;
		}
		i++;
	}
}

int	ft_unset(char **argv)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (argv[i])
	{
		if (ft_valid_name(argv[i]))
		{
			ft_delete_key(argv[i]);
		}
		else
		{
			ret = 1;
			ft_put_err_simple("minishell: unset: `");
			ft_put_err_simple(argv[i]);
			ft_put_err_simple("': not a valid identifier\n");
		}
		i++;
	}
	return (ret);
}
