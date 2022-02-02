//
// Created by sergey on 01.02.2022.
//
#include "../includes/mini_shell.h"

void print_env(char **env)
{
	while (*env)
	{
		printf("%s", *env++);
		printf("\n");
	}
}

int main(int argc, char **argv, char **env)
{

}