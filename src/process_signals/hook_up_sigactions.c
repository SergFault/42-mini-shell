//
// Created by sergey on 02.02.2022.

#include "../../includes/minishell.h"

extern int	g_status;

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
		exit(g_status);
	}

	if (sig_no == SIGQUIT)
	{
		exit(g_status);
	}
}

void hook_signals()
{
	signal(SIGINT, sig_handler);
}