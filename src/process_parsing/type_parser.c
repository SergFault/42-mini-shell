//
// Created by sergey on 06.02.2022.
//

#include <stdbool.h>
#include "../../includes/mini_shell.h"

bool is_file_in_op(t_list *pList);

bool is_here_doc(t_list *pList);

bool is_file_out_append(t_list *pList);

bool is_file_out_op(t_list *pList);

bool is_file_out_append_op(t_list *pList);

bool is_in_file(t_list *pList);

bool is_lim(t_list *pList);

bool is_out_file(t_list *pList);

bool is_arg(t_list *pList);

int set_types(t_list *elements){
	while(elements){
		if (is_file_in_op(elements))
			get_word(elements)->t = FILE_IN_OP;
		else if (is_here_doc(elements))
			get_word(elements)->t = HERE_DOC_OP;
		else if (is_file_out_op(elements))
			get_word(elements)->t = FILE_OUT_OP;
		else if (is_file_out_append_op(elements))
			get_word(elements)->t = FILE_OUT_APPEND_OP;
		else if (is_in_file(elements))
			get_word(elements)->t = IN_FILE;
		else if (is_lim(elements))
			get_word(elements)->t = LIM;
		else if (is_out_file(elements))
			get_word(elements)->t = OUT_FILE;
		else if (is_file_out_append(elements))
			get_word(elements)->t = FILE_OUT_APPEND;
		else if (is_arg(elements))
			get_word(elements)->t = ARG;
		elements = elements->next;
	}
}

bool is_arg(t_list *pList)
{
	return 1;
}

bool is_out_file(t_list *pList)
{
	return 0;
}

bool is_lim(t_list *pList)
{
	return 0;
}

bool is_in_file(t_list *pList)
{
	return 0;
}

bool is_file_out_append_op(t_list *pList)
{
	return 0;
}

bool is_file_out_op(t_list *pList)
{
	return 0;
}

bool is_file_out_append(t_list *pList)
{
	return 0;
}

bool is_here_doc(t_list *pList)
{
	return 0;
}

bool is_file_in_op(t_list *pList)
{
	return 0;
}
