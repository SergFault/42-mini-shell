//
// Created by sergey on 03.02.2022.
//

#include "../../includes/mini_shell.h"

int char_arr_size(char **char_arr){
	int count;
	int pos;

	count = 0;
	pos = 0;
	while(char_arr[pos]){
		count++;
		pos++;
	}
	return count;
}
