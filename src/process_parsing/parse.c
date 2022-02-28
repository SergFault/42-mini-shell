#include "../../includes/minishell.h"


t_word *cut_word(int s_pos, int c_pos, char *line)
{
	char	*word_str;
	t_word	*word;

	word_str = malloc(sizeof (char) * (c_pos - s_pos + 1));
	word = malloc(sizeof(t_list));
	if (!word_str || !word){
		ft_putstr_fd("Memory allocation error.\n", 2);
		return NULL;
	}
	word_str[c_pos - s_pos] = '\0';
	ft_strncpy(word_str, line + s_pos, c_pos - s_pos);
	word->val = word_str;
	word->t = NONE;
	return (word);
}

t_list *get_words(char *line){
	t_list *words_lst;
	t_word *word;
	int len;
	int	s_pos;
	int	c_pos;

	words_lst = NULL;
	len = ft_strlen(line);
	c_pos = 0;
	while (c_pos < len)
	{
		while (c_pos < len && line[c_pos] == ' ')
			c_pos++;
		if (c_pos >= len)
			break ;
		s_pos = c_pos;
		if (line[c_pos] == '>' || line[c_pos] == '<')
			skip_redir(line, &c_pos);
		else
			skip_arg(line, &c_pos);
		word = cut_word(s_pos, c_pos, line);
		ft_lstadd_back(&words_lst, ft_lstnew(word));
	}
	return (words_lst);
}

t_list *parse_elements(char *line){

	t_list	*iter;
	t_list	*words_lst;

	words_lst = get_words(line);
	set_types(words_lst);
	iter = words_lst;
	while (iter)
	{
		ft_substitution(&(get_word(iter)->val));
		ft_unquote(&(get_word(iter)->val));
		iter = iter->next;
	}

	//todo debug only (print words)
	iter = words_lst;
	while (iter)
	{
//		print_word(iter);
		iter= iter->next;
	}
	return words_lst;
}

int   fill_words(t_list *cmd){

	while(cmd)
	{
		get_cmd(cmd)->element = parse_elements(get_cmd(cmd)->cmd_line); //todo make proper parsing
		cmd = cmd->next;
	}
	return (0);
}

t_list *map_lines_cmds(char **lines)
{
	int pos;
	t_command *cmd;
	t_list *cmd_lst;

	cmd_lst = NULL;
	pos = -1;
	while (lines[++pos])
	{
		cmd = malloc(sizeof(t_command));
		cmd->cmd_line = lines[pos];
		cmd->element = NULL;
		ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
	}
	return cmd_lst;
}


t_list *parse_input(char **input_p){
	t_list *command_lst;
	char **lines;
	char *input = *input_p;
	command_lst = NULL;

	if (is_quotes_open(input))
	{
		ft_putstr_fd(PROMPT, 2);
		ft_putstr_fd("Parsing error: quotes\n", 2);
		return (NULL);
	}
	lines = ft_split_pipes(input);
	command_lst = map_lines_cmds(lines);
	free(lines);
	fill_words(command_lst);
	return command_lst;
}

