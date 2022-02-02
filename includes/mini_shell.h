#ifndef MINI_SHELL_H
#define MINI_SHELL_H

/* unchecked */
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>

/* readline */
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/* signals */
#include <signal.h>

/* utils */
#include <stdlib.h>

# define PROMPT "original:"

int parse(void);
int launch_commands();

/* signals */
int hook_signals(struct sigaction *actions);
void ft_exit();

#endif
