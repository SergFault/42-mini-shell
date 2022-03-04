/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:26:00 by eshana            #+#    #+#             */
/*   Updated: 2022/03/05 01:20:59 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_keycmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && s1[i] != '=' && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] == '=' && (s2[i] == '=' || !s2[i]) || s2[i] == '=' && (s1[i] == '=' || !s1[i]))
		return (0);
	return (s1[i] - s2[i]);
}

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

int	ft_keylen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
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
		{
			key[i + 1] = '\0';
			break;
		}
	}
	i = 0;
	while (g_env[i])
	{
		if (!ft_keycmp(key, g_env[i]))
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

char	*ft_find_min(char **tmp, int size)
{
	int		i;
	int		res;
	char 	*str;

	i = 0;
	while (tmp[i] == NULL && i < size)
		i++;
	res = i;
	str = tmp[i];
	if (!str)
		return (NULL);
	i++;
	while (i < size)
	{
		if (tmp[i] != NULL)
			if (ft_strncmp(tmp[i], str, ft_strlen(tmp[i])) < 0)
			{
				str = tmp[i];
				res = i;
			}
		i++;
	}
	tmp[res] = NULL;
	return (str);
}

void	ft_print_env(void)
{
	char	*str;
	char 	**tmp;
	int		size;
	int		i;

	size = ft_str_arr_size(g_env);
	tmp = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (g_env[i])
	{
		tmp[i] = g_env[i];
		//if (!ft_value_changed(tmp[i]))
			//tmp[i] = NULL;
		i++;
	}
	i = 0;
	while (i < size)
	{
		str = ft_find_min(tmp, size);
		if (!str)
			break ;
		printf("declare -x ");
		while (*str)
		{
			printf("%c", *str);
			if (*str == '=')
			{
				printf("\"%s\"", str + 1);
				break ;
			}
			str++;
		}
		printf("\n");
		i++;
	}
	free(tmp);
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
	if (i == 1)
		ft_print_env();
	return (ret);
}
