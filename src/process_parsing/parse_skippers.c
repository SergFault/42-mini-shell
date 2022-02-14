//
// Created by sergey on 14.02.2022.
//
#include "minishell.h"

void skip_arg(char *line, int *c_pos)
{
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	while (line[(*c_pos)])
	{
		change_quote_flags(quotes, line + *c_pos);
		if (is_delim(line[*c_pos]) == 1 && !(quotes[0] || quotes[1]))
			break ;
		(*c_pos)++;
	}
}

void skip_redir(char *line, int *pos)
{
	char skip_ch;

	skip_ch = line[*pos];
	while (line[*pos] && line[*pos] == skip_ch)
		(*pos)++;
}