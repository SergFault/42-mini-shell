//
// Created by sergey on 06.02.2022.
//

#include "../../includes/minishell.h"

void free_cmd(void* cmd){
		free(((t_command *) cmd)->cmd_line);
		ft_lstclear(&((t_command *) cmd)->element, free_word);
		free(cmd);
}

void free_word(void* word){
	if (word)
	{
		free(((t_word *) word)->val);
		free(word);
	}
}

void free_cmds(t_list **cmds){
	if (cmds)
		ft_lstclear(cmds, free_cmd);
}

void free_all(t_list *cmds)
{
	rl_clear_history();
	free_cmds(&cmds);
	free_str_arr(g_env);
}
