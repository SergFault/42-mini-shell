/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:25:47 by eshana            #+#    #+#             */
/*   Updated: 2022/03/06 23:45:45 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env_addr(const char *key)
{
	int		i;
	int		res;

	i = 0;
	while (g_data.env[i])
	{
		res = ft_strncmp(g_data.env[i], key, ft_strlen(key));
		if (!res)
			return (g_data.env[i]);
		i++;
	}
	return (NULL);
}

void	ft_rewrite_pwd(char *pwd, char *oldpwd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (g_data.env[i])
	{
		if (!ft_strncmp(g_data.env[i], "PWD=", ft_strlen("PWD=")))
		{
			free(g_data.env[i]);
			g_data.env[i] = pwd;
			pwd = NULL;
		}
		if (!ft_strncmp(g_data.env[i], "OLDPWD=", ft_strlen("OLDPWD=")) ||
			!ft_strcmp(g_data.env[i], "OLDPWD"))
		{
			free(g_data.env[i]);
			g_data.env[i] = oldpwd;
			oldpwd = NULL;
		}
		i++;
	}
	if (pwd)
		free(pwd);
	if (oldpwd)
		free(oldpwd);
}

int	ft_cd(char **argv)
{
	int		ret;
	char	*pwd;
	char 	*oldpwd;
	char 	*buf;

	if (ft_str_arr_size(argv) > 2)
	{
		ft_put_err("minishell: cd: too many arguments\n");
		return (1);
	}
	if (argv[1])
		ret = chdir(argv[1]);
	if (!ret)
	{
		pwd = ft_get_env_addr("PWD=");
		oldpwd = ft_strjoin("OLD", pwd);
		buf = (char *)malloc(sizeof(char) * (PATH_MAX + 1));
		pwd = ft_strjoin("PWD=", getcwd(buf, PATH_MAX));
		free(buf);
		ft_rewrite_pwd(pwd, oldpwd);
		return (0);
	}
	ft_put_err("minishell: cd: ");
	perror(argv[1]);
	return(1);
}
