#include "minishell.h"

size_t	ft_count_digits(int n)
{
	if (n < 10 && n > -10)
		return (1);
	else
		return (1 + ft_count_digits(n / 10));
}

int	ft_abs(int n)
{
	if (n >= 0)
		return (n);
	return (-n);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sgn;
	size_t	size;

	sgn = 0;
	size = ft_count_digits(n);
	if (n < 0)
		sgn = 1;
	str = (char *)malloc(sizeof(char) * (size + sgn + 1));
	if (str)
	{
		if (sgn)
			str[0] = '-';
		if (n == 0)
			str[0] = '0';
		while (n)
		{
			str[sgn + size - 1] = '0' + ft_abs(n % 10);
			size--;
			n /= 10;
		}
	}
	return (str);
}

char	**ft_new_shlvl(char **env)
{
	char	**var;
	char	*shlevel;
	char	*newlevel;

	var = (char **)malloc(sizeof(char *) * 3);
	var[2] = NULL;
	var[0] = ft_strdup("export");
	shlevel = get_env_var(env, "SHLVL");
	newlevel = ft_itoa(ft_atoi(shlevel) + 1);
	var[1] = ft_strjoin("SHLVL=", newlevel);
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