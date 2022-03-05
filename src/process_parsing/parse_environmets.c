#include "minishell.h"

int parse_environment(char **env){
	int count;
	int pos;

	pos = 0;
	count = ft_str_arr_size(env);
	g_data.env = (char **)malloc(sizeof(char *) * (count + 1));
	while(env[pos]){
		g_data.env[pos] = ft_strdup(env[pos]);
		pos++;
	}
	g_data.env[pos] = NULL;
	return (0);
}