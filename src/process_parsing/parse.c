//
// Created by sergey on 01.02.2022.
//

#include "../../includes/minishell.h"

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
	words = ft_split(cmd_line, ' '); //todo make proper parsing
	while(words[++pos]){
		word = (t_word *) malloc(sizeof (t_word));
		word->val = words[pos];
		word->t = ARG; //todo delete when type_parser done
		ft_lstadd_back(&elements, ft_lstnew(word));
	}
	set_types(elements);
	free(words);
	return elements;
}


int   parse_2(t_list *cmd){

	while(cmd)
	{
		get_cmd(cmd)->element = parse_elements(get_cmd(cmd)->cmd_line); //todo make proper parsing
		cmd = cmd->next;
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
	g_env[pos] = NULL;
	return (0);
}

t_list *parse_input(char *input){
	t_list *command_lst;
	t_command *cmd;
	char **lines;
	int pos;
	command_lst = NULL;
	lines = parse_1(input); //todo make proper parsing considering quotes
	pos = -1;
	while (lines[++pos])
	{
		cmd = malloc(sizeof(t_command));
		cmd->cmd_line = lines[pos];
		cmd->element = NULL;
		ft_lstadd_back(&command_lst, ft_lstnew(cmd));
	}
	free(lines);
	parse_2(command_lst); //todo make proper parsing considering quotes
	print_cmds(command_lst);
	return command_lst;
}