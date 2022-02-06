//
// Created by sergey on 04.02.2022.
//

#include "../../includes/minishell.h"

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

int	ft_exit(char **params, t_list *cmd_to_free)
{
	unsigned char	ret;
	int				size;

	size = ft_str_arr_size(params);
	ret = 0;
	if (size > 1 && ft_is_numeric(params[1]))
	{
		if (size > 2)
		{
			printf("exit\ntoo many args\n");
			//free args
			return (1);//error: too many arguments
		}
		else
			ret = ft_atoi(params[1]);
	}
	else if (size > 1)
	{
		//error: numeric argument required
		ret = 2;
	}
	printf("exit\n");
	free_all(cmd_to_free);
	free(params);
	exit(ret);
}
