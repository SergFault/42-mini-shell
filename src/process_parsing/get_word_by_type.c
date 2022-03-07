//
// Created by sergey on 08.02.2022.
//

#include "minishell.h"

t_word *get_word_by_type(t_list *cmd, enum e_type t){
	t_command *command;
	t_list *word_lst;

	command = get_cmd(cmd);
	word_lst = command->element;
	while(word_lst)
	{
		if (get_word(word_lst)->t == t)
			return (get_word(word_lst));
		word_lst = word_lst->next;
	}
	return NULL;
}