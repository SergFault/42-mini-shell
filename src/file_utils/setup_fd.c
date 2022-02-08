
#include <fcntl.h>
#include "minishell.h"

int setup_redirect_write(t_list *command)
{
	int f;
	t_word *word;

	word = get_word_by_type(command, FILE_OUT_APPEND);
	if (word)
	{
		f = open( word->val, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (f == -1)
		{
			f = open("/dev/null", O_WRONLY);
			printf("Permission denied\n"); //todo error
		}
		dup2(f, 1);
	}
	return (0);
}

int setup_redirect(t_list *command){
	int f;
	t_word *word;

	word = get_word_by_type(command, OUT_FILE);
	if (word)
	{
		f = open( word->val, O_WRONLY | O_CREAT, 0664);
		if (f == -1)
		{
			f = open("/dev/null", O_WRONLY);
			printf("Permission denied\n"); //todo error
		}
		dup2(f, 1);
	}
	return (0);
}

int setup_fd(t_list *command){
	setup_redirect(command);
	setup_redirect_write(command);
	return (0);
}


