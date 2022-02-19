/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:26:00 by eshana            #+#    #+#             */
/*   Updated: 2022/02/19 03:51:51 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ltrs_undersc(char c)
{
	if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_')
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
			if (ft_ltrs_undersc(name[i]) || name[i] >= '0' && name[i] <= '9')
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

int	ft_add_key(char *name)
{
	char	*key;
	int		i;
	char 	**new_env;

	i = 0;
	key = ft_strdup(name);
	while (key[i])
	{
		i++;
		if (key[i] == '=')
			key[i] = '\0';
	}
	i = 0;
	while (g_env[i])
	{
		if (ft_strnstr(g_env[i], key, ft_strlen(key)))
		{
			if (ft_value_changed(name))
			{
				free(g_env[i]);
				g_env[i] = ft_strdup(name);
			}
			free(key);
			return (0);
		}
		i++;
	}
	free(key);
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	new_env[i + 1] = NULL;
	new_env[i] = ft_strdup(name);
	while (--i >= 0)
		new_env[i] = g_env[i];
	free(g_env);
	g_env = new_env;
	return (0);
}

int	ft_export(char **argv)
{
	int	i;
	int ret;

	i = 1;
	ret = 0;
	while (argv[i])
	{
		if (ft_valid_name(argv[i]))
		{
			ft_add_key(argv[i]);
		}
		else
		{
			ret = 1;
			ft_put_err("minishell: export: `");
			ft_put_err(argv[i]);
			ft_put_err("': not a valid identifier\n");
		}
		i++;
	}
	return (ret);
}
