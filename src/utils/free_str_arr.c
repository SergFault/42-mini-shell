//
// Created by sergey on 06.02.2022.
//

#include "../../includes/mini_shell.h"

void free_str_arr(char ** str_arr){
	char **temp;

	temp = str_arr;
	while(*str_arr){
		free(*str_arr);
		str_arr++;
	}
	free(temp);
}