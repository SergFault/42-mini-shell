#ifndef MINI_SHELL_H
#define MINI_SHELL_H

/*unchecked*/
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>

int parse(void);
int launch_commands();

#endif
