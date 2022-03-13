/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:25:47 by eshana            #+#    #+#             */
/*   Updated: 2022/03/07 18:48:59 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_env_addr(const char *key)
{
	int		i;
	int		res;

	i = 0;
	while (g_data.env[i])
	{
		res = ft_strncmp(g_data.env[i], key, ft_strlen(key));
		if (!res && (g_data.env[i][ft_strlen(key)] == '='
			|| g_data.env[i][ft_strlen(key)] == '\0'))
			return (g_data.env[i]);
		i++;
	}
	return (NULL);
}

static void	ft_rewrite_pwd(char *pwd, char *oldpwd)
{
	int		i;

	i = 0;
	while (g_data.env[i])
	{
		if (!ft_strncmp(g_data.env[i], "PWD=", ft_strlen("PWD="))
			|| !ft_strcmp(g_data.env[i], "PWD"))
		{
			free(g_data.env[i]);
			g_data.env[i] = pwd;
			pwd = NULL;
		}
		if (!ft_strncmp(g_data.env[i], "OLDPWD=", ft_strlen("OLDPWD="))
			|| !ft_strcmp(g_data.env[i], "OLDPWD"))
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

static void	ft_free_resources(char **argv, char *dir)
{
	if (!argv[1])
		free(dir);
}

static int	ft_process_chdir(char **argv, char *dir)
{
	char	*buf;
	char	*pwd;
	char	*oldpwd;

	pwd = ft_get_env_addr("PWD");
	oldpwd = ft_strjoin("OLD", pwd);
	buf = (char *) malloc(sizeof(char) * (PATH_MAX + 1));
	fatal_err_if(buf == NULL, NULL);
	pwd = ft_strjoin("PWD=", getcwd(buf, PATH_MAX));
	free(buf);
	ft_rewrite_pwd(pwd, oldpwd);
	ft_free_resources(argv, dir);
	return (0);
}

int	ft_cd(char **argv)
{
	int		ret;
	char	*dir;

	dir = argv[1];
	if (!dir)
	{
		dir = ft_get_env_addr("HOME");
		if (dir && dir[4] == '=')
			dir = get_env_var(g_data.env, "HOME");
		else
			dir = NULL;
	}
	if (dir)
	{
		ret = chdir(dir);
		if (!ret || !ft_strlen(dir))
			return (ft_process_chdir(argv, dir));
		ft_put_err_simple("minishell: cd: ");
		perror(dir);
		ft_free_resources(argv, dir);
		return (1);
	}
	ft_put_err_simple("minishell: cd: HOME not set\n");
	return (1);
}
