/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:49:51 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/07 18:53:41 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

int	ft_isspace(char c)
{
	if ((c == ' ') || ((c > 8) && (c < 14)))
		return (1);
	return (0);
}

int	ft_is_numeric(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '+' || str[i] == '-')
			i++;
		while (str[i] >= '0' && str[i] <= '9')
			i++;
		while (ft_isspace(str[i]))
			i++;
		if (str[i])
			return (0);
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		res;
	int		sgn;

	sgn = 1;
	i = 0;
	res = 0;
	while ((str[i] == ' ') || ((str[i] > 8) && (str[i] < 14)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sgn = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sgn);
}

static void	numeric_err(char *param)
{
	ft_put_err_simple("minishell: exit: ");
	ft_put_err_simple(param);
	ft_put_err_simple(": numeric argument required\n");
}

int	ft_exit(char **params, t_list *cmd_to_free)
{
	int				size;

	size = ft_str_arr_size(params);
	printf("exit\n");
	if (size > 1)
	{
		if (size > 2 && ft_is_numeric(params[1]))
		{
			ft_put_err_simple("minishell: exit: too many arguments\n");
			return (1);
		}
		else if (ft_is_numeric(params[1]))
			g_data.ret_val = ft_atoi(params[1]) % 256;
		else
		{
			g_data.ret_val = 255;
			numeric_err(params[1]);
		}
		free_all(cmd_to_free);
		free(params);
		exit(g_data.ret_val);
	}
	free_all(cmd_to_free);
	free(params);
	exit(g_data.ret_val);
}
