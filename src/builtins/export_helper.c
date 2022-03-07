/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecport_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:04:11 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/07 19:16:44 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ltrs_undersc(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int	ft_valid_name(const char *name)
{
	int	i;

	i = 0;
	if (ft_ltrs_undersc(name[i++]))
	{
		while (name[i] && name[i] != '=')
		{
			if (ft_ltrs_undersc(name[i]) || (name[i] >= '0' && name[i] <= '9'))
			{
				i++;
				continue ;
			}
			return (0);
		}
		return (1);
	}
	return (0);
}

int	ft_value_changed(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	cut_key(char *key)
{
	int		i;

	i = 0;
	while (key[i])
	{
		i++;
		if (key[i] == '=')
		{
			key[i + 1] = '\0';
			break ;
		}
	}
}

int	change_val(char *name, char *key, int *i)
{
	while (g_data.env[*i])
	{
		if (!ft_keycmp(key, g_data.env[*i]))
		{
			if (ft_value_changed(name))
			{
				free(g_data.env[*i]);
				g_data.env[*i] = ft_strdup(name);
			}
			free(key);
			return (0);
		}
		(*i)++;
	}
	return (1);
}
