
#include "minishell.h"

int is_delim(char i)
{
	return (i == ' ' || i == '>' || i == '<');
}