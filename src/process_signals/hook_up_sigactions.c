//
// Created by sergey on 02.02.2022.

#include "../../includes/mini_shell.h"

void sig_handler(int sig_no)
{
	if (sig_no == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}

	if (sig_no == SIGTERM){
		ft_exit(0, NULL);
	}

	if (sig_no == SIGQUIT)
	{
		ft_exit(0, NULL);
	}
}

int hook_signals()
{
	signal(SIGINT, sig_handler);
	return (1);

}