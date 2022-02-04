
#include "../../includes/mini_shell.h"

char *get_env_var(char **var_arr, const char *key)
{
	int i;
	char *var_val;

	i = 0;
	while (var_arr[i])
	{
		var_val = ft_strnstr(var_arr[i], key, strlen(key));
		if (var_val)
			return var_val;
		i++;
	}
	return (NULL);
}