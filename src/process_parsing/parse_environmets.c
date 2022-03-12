/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_environmets.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:40:33 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/12 14:22:12 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_new_shlvl(char **env)
{
	char	**var;
	char	*shlevel;
	char	*newlevel;
	char	*buf;

	var = (char **)malloc(sizeof(char *) * 6);
	var[5] = NULL;
	var[0] = ft_strdup("export");
	shlevel = get_env_var(env, "SHLVL");
	newlevel = ft_itoa(ft_atoi(shlevel) + 1);
	var[1] = ft_strjoin("SHLVL=", newlevel);
	var[2] = ft_strdup("SHELL=minishell");
	var[3] = ft_strdup("OLDPWD");
	buf = (char *) malloc(sizeof(char) * (PATH_MAX + 1));
	var[4] = ft_strjoin("PWD=", getcwd(buf, PATH_MAX));
	free(buf);
	free(shlevel);
	free(newlevel);
	return (var);
}

char	**ft_unset_pwd(void)
{
	char	**argv;

	argv = (char **)malloc(sizeof(char *) * 3);
	if (argv)
	{
		argv[2] = NULL;
		argv[0] = ft_strdup("PWD");
		argv[1] = ft_strdup("OLDPWD");
	}
	return (argv);
}

int	parse_environment(char **env)
{
	int		count;
	int		pos;
	char	**var;

	pos = 0;
	count = ft_str_arr_size(env);
	g_data.env = (char **)malloc(sizeof(char *) * (count + 1));
	while (env[pos])
	{
		g_data.env[pos] = ft_strdup(env[pos]);
		pos++;
	}
	g_data.env[pos] = NULL;
	var = ft_unset_pwd();
	ft_unset(var);
	free_str_arr(var);
	var = ft_new_shlvl(env);
	ft_export(var);
	free_str_arr(var);
	return (0);
}
