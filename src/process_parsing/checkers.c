
#include "minishell.h"

int is_delim(char i)
{
	return (i == ' ' || i == '>' || i == '<');
}


int	have_empty_cmds(t_list *commands_list)
{
	while (commands_list)
	{
		if  (consider_empty(get_cmd(commands_list)->cmd_line))
			return (1);
		commands_list = commands_list->next;
	}
	return (0);
}