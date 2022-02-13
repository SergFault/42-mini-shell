//
// Created by sergey on 08.02.2022.
//

#include "minishell.h"

char *get_random_name()
{
	int c;
	int f;
	char *name;
	int number;

	c = 9;
	name = (char *)malloc(sizeof(char) * c);
	if (!name){
		printf("error"); //todo correct error handle
		return (NULL);
	}
	f = open("/dev/random", O_RDONLY);
	if (f == -1)
	{
		printf("error"); //todo correct error handle
		return (NULL);
	}
	name[--c] = '\0';
	while(--c >= 0){
		read(f, &number, 1);
		if (number < 0)
			number = number * (-1);
		name[c] = (char)('a' + (number % 26));
	}
	return name;
}

int here_doc_fd(char *delim){
	int f;
	char *input;
	char *ptr;
	char *file_name;
	char *full_path;
	char *to_free;

	file_name = get_random_name();
	full_path = ft_strjoin("./temp/", file_name);
	printf("fullpath %s\n", full_path);
	f = open(full_path, O_CREAT | O_EXCL | O_RDWR, 0644);
	if (f == -1)
	{
		printf("error"); //todo correct error handle
	}
	input = readline(NULL);
	while (input)
	{
		to_free = input;
		input = ft_strjoin(input, "\n");
		free(to_free);
		ptr = ft_strnstr(input, delim, strlen(input));
		if (ptr)
		{
			while (input != ptr)
			{
				write(f, input, 1);
				input++;
			}
			break ;
		}
		ft_putstr_fd(input, f);
		input = readline(NULL);
	}
	close(f);
	f = open(full_path, O_RDONLY);
	free(full_path);
	return (f);
}