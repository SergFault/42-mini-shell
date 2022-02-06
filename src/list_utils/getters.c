
#include "../../includes/mini_shell.h"

t_command *get_cmd(t_list *lst){
	return lst->content;
}

t_word *get_word(t_list *lst){
	return lst->content;
}

char **get_args(t_list *command)
{

	t_list *iter;
	char **args;
	iter = get_cmd(command)->element;
	int args_count;
	int pos;

	args_count = 0;
	while (iter)
	{
		if (get_word(iter)->t == ARG)
			args_count++;
		iter = iter->next;
	}
	args = (char **) malloc(sizeof(char *) * (args_count + 1));
	iter = get_cmd(command)->element;
	pos = -1;
	while (iter)
	{
		if (get_word(iter)->t == ARG)
			args[++pos] = get_word(iter)->val;
		iter = iter->next;
	}
	args[++pos] = NULL;
	return args;
}