//
// Created by sergey on 06.02.2022.
//

#include "../../includes/mini_shell.h"

void free_cmd(void* cmd){
	free(((t_command *)cmd)->cmd_line);
	ft_lstclear( &((t_command *)cmd)->element, free_word);
	free((t_command *)cmd);
}

void free_word(void* word){
	free(((t_word *)word)->val);
}


void free_cmds(t_list **cmds){
	ft_lstclear(cmds, free_cmd);
}
