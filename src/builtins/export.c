/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:26:00 by eshana            #+#    #+#             */
/*   Updated: 2022/03/11 14:53:08 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_key(char *name)
{
	char	*key;
	int		i;
	char	**new_env;

	key = ft_strdup(name);
	cut_key(key);
	i = 0;
	if (change_val(name, key, &i) == 0)
		return (0);
	free(key);
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	new_env[i + 1] = NULL;
	new_env[i] = ft_strdup(name);
	while (--i >= 0)
		new_env[i] = g_data.env[i];
	free(g_data.env);
	g_data.env = new_env;
	return (0);
}

char	*ft_find_min(char **tmp, int size)
{
	int		i;
	int		res;
	char	*str;

	i = 0;
	while (tmp[i] == NULL && i < size)
		i++;
	res = i;
	str = tmp[i++];
	if (!str)
		return (NULL);
	while (i < size)
	{
		if (tmp[i] != NULL)
		{
			if (ft_strncmp(tmp[i], str, ft_strlen(tmp[i])) < 0)
			{
				str = tmp[i];
				res = i;
			}
		}
		i++;
	}
	tmp[res] = NULL;
	return (str);
}

void	prnt(char *str)
{
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
}

void	ft_print_env(void)
{
	char	*str;
	char	**tmp;
	int		size;
	int		i;

	size = ft_str_arr_size(g_data.env);
	tmp = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (g_data.env[i])
	{
		tmp[i] = g_data.env[i];
		i++;
	}
	tmp[i] = g_data.env[i];
	i = 0;
	while (i++ < size)
	{
		str = ft_find_min(tmp, size);
		if (!str)
			break ;
		printf("declare -x ");
		prnt(str);
		printf("\n");
	}
	free(tmp);
}

int	ft_export(char **argv)
{
	int	i;
	int	ret;

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
