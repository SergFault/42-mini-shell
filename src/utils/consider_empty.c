//
// Created by sergey on 03.02.2022.
//

static int is_inconsiderable(char ch)
{
	if (ch == ' ' || ch == '\f' || ch == '\n'
		|| ch == '\r' || ch == '\t' || ch == '\v')
		return 1;
	else
		return 0;
}

int consider_empty(char *str)
{
	int is_empty;

	is_empty = 1;
	while (*str)
	{
		if (!is_inconsiderable(*str))
		{
			return (0);
		} else
		{
			str++;
		}
	}
	return (1);
}