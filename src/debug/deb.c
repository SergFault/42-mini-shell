//
// Created by sergey on 08.02.2022.
//

#include "../../includes/minishell.h"

void print_word(t_list *word)
{
	printf("<<word>>\n");
	printf("	VALUE:%s\n", get_word_str(word));
	if (is_file_in_op(word))
		printf("	FILE_IN_OP\n");
	else if (is_here_doc(word))
		printf("	HERE_DOC_OP\n");
	else if (is_file_out_append(word))
		printf("	FILE_OUT_APPEND\n");
	else if (is_file_out_op(word))
		printf("	FILE_OUT_OP\n");
	else if (is_file_out_append_op(word))
		printf("	FILE_OUT_APPEND_OP\n");
	else if (is_in_file(word))
		printf("	IN_FILE\n");
	else if (is_lim(word))
		printf("	LIM\n");
	else if (is_out_file(word))
		printf("	OUT_FILE\n");
	else
		printf("	ARG\n");
}

//todo debug only
void print_cmds(t_list *cmd){
	t_list *iter_word;

	while (cmd){
		iter_word = (((t_command *)cmd->content)->element);
		while(iter_word)
		{
			print_word(iter_word);
			iter_word = iter_word->next;
		}
		cmd = cmd->next;
	}
}

void print_str_arr(char **str_arr){

	char **iter;

	iter = str_arr;
	while (*iter != NULL)
	{
		printf("%s\n", *iter);
		iter++;
	}
}

