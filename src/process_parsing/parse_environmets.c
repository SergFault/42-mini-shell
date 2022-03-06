#include "minishell.h"

char	**ft_new_shlvl(char **env)
{
	char	**var;
	char	*shlevel;
	char	*newlevel;

	var = (char **)malloc(sizeof(char *) * 5);
	var[4] = NULL;
	var[0] = ft_strdup("export");
	shlevel = get_env_var(env, "SHLVL");
	newlevel = ft_itoa(ft_atoi(shlevel) + 1);
	var[1] = ft_strjoin("SHLVL=", newlevel);
	var[2] = ft_strdup("SHELL=minishell");
	var[3] = ft_strdup("OLDPWD");
	free(shlevel);
	free(newlevel);
	return (var);
}

int parse_environment(char **env)
{
	int		count;
	int		pos;
	char	**var;

	pos = 0;
	count = ft_str_arr_size(env);
	g_data.env = (char **)malloc(sizeof(char *) * (count + 1));
	var = ft_new_shlvl(env);
	while(env[pos])
	{
		g_data.env[pos] = ft_strdup(env[pos]);
		pos++;
	}
	g_data.env[pos] = NULL;
	ft_export(var);
	pos = 0;
	while (var[pos])
		free(var[pos++]);
	free(var);
	return (0);
}
