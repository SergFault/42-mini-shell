//
// Created by sergey on 02.02.2022.

#include "../../includes/mini_shell.h"

void interrupt_handler()
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int hook_signals(struct sigaction *actions)
{

	actions[0].sa_handler = ft_exit;
	sigaction(SIGQUIT, actions, NULL);
	actions[1].sa_handler = interrupt_handler;
	sigaction(SIGINT, actions + 1, NULL);
	actions[2].sa_handler = ft_exit;
	sigaction(SIGTERM, actions + 2, NULL);

	return (1);

}