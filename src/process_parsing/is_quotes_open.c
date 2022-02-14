//
// Created by sergey on 13.02.2022.
//

void change_quote_flags(int *q_flags, const char *ch)
{
	if ((*ch == '\'') && (!q_flags[1]) && (!q_flags[0]))
		q_flags[0] = 1;
	else if ((*ch == '\'') && (q_flags[0]))
		q_flags[0] = 0;
	else if ((*ch == '\"') && (!q_flags[1]) && (!q_flags[0]))
		q_flags[1] = 1;
	else if ((*ch == '\"') && (q_flags[1]))
		q_flags[1] = 0;
}

int is_quotes_open(char *str){
	int in_quotes[2];

	in_quotes[0] = 0;
	in_quotes[1] = 0;
	if (!str)
		return 0;
	while (*str)
	{
		change_quote_flags(in_quotes, str);
		str++;

	}
	return (in_quotes[0] || in_quotes[1]);
}