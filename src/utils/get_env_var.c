
#include "../../includes/minishell.h"

char *get_env_var(char **var_arr, const char *key)
{
	int i;
	char *var_val;
	char *full_key;
	int key_size;

	full_key = ft_strjoin(key, "=");
	i = 0;
	while (var_arr[i])
	{
		var_val = ft_strnstr(var_arr[i], full_key, ft_strlen(full_key));
		if (var_val){
			key_size = strlen(full_key);
			free(full_key);
			return (ft_strdup(var_val + key_size));
		}
		i++;
	}
	free(full_key);
	return (ft_strdup(""));
}
