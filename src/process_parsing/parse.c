//
// Created by sergey on 01.02.2022.
//

#include "../../includes/mini_shell.h"

/* single quotes, quotes, escape char*/
//process_escape_characters(){
//
//}

/* check input mistakes */
//process_errors(){
//
//}

/* set environment to command. Example: $pwd = /etc */
//set_env(){
//
//}

/* find binary file at $PATH */
//find_binary(){
//
//}

/* decompose commands */
//commands_decomposition(){
//
//}

//int parse(){
//	process_escape_characters();
//	process_errors();
//	set_env();
//	find_binary();
//	commands_decomposition();
//	return 0;
//}

int parse_environment(char **env){
	int count;
	int pos;

	pos = 0;
	count = char_arr_size(env);
	g_env = (char **)malloc(sizeof(char *) * (count + 1));
	while(env[pos]){
		g_env[pos] = ft_strdup(env[pos]);
		pos++;
	}
	return (0);
}