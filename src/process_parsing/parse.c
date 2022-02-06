//
// Created by sergey on 01.02.2022.
//

#include "../../includes/mini_shell.h"

t_list *parse_elements();

char **parse_1(char *input){
	return ft_split(input, '|');
}

t_list *parse_elements(char *cmd_line)
{
	t_list *elements;
	elements = NULL;
	char ** words;
	int pos;
	t_word *word;

	pos = -1;
	words = ft_split(cmd_line, ' ');
	while(words[++pos]){
		word = (t_word *) malloc(sizeof (t_word));
		word->val = words[pos];
		word->t = ARG;
		ft_lstadd_back(&elements, ft_lstnew(word));
	}
	return elements;
}


int   parse_2(t_list *pipe_lst){

	while(pipe_lst)
	{
		get_cmd(pipe_lst)->element = parse_elements(get_cmd(pipe_lst)->cmd_line); //todo make proper parsing
		pipe_lst = pipe_lst->next;
	}
	return (0);
}


int parse_environment(char **env){
	int count;
	int pos;

	pos = 0;
	count = ft_str_arr_size(env);
	g_env = (char **)malloc(sizeof(char *) * (count + 1));
	while(env[pos]){
		g_env[pos] = ft_strdup(env[pos]);
		pos++;
	}
	return (0);
}

t_list *parse_input(char *input){
	t_list *command_lst;
	t_command *p_line;
	char **lines;
	int pos;
	command_lst = NULL;
	lines = parse_1(input); //todo make proper parsing considering quotes
	pos = -1;
	while (lines[++pos])
	{
		p_line = malloc(sizeof(t_command));
		p_line->cmd_line = lines[pos];
		p_line->element = NULL;
		ft_lstadd_back(&command_lst, ft_lstnew(p_line));
	}
	parse_2(command_lst); //todo make proper parsing considering quotes
	return command_lst;
}