/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:25:03 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/14 17:31:01 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_err(char *str_err)
{
	ft_putstr_fd(str_err, 2);
	ft_free_exit_err(2);
}

char	*get_random_name(void)
{
	int		c;
	int		f;
	char	*name;
	int		number;

	number = 0;
	c = 9;
	name = (char *)malloc(sizeof(char) * c);
	if (!name)
		process_err("fatal: memory allocation error");
	f = open("/dev/random", O_RDONLY);
	if (f == -1)
		process_err("fatal: resource access error");
	name[--c] = '\0';
	while (--c > 0)
	{
		read(f, &number, 1);
		if (number < 0)
			number = number * (-1);
		name[c] = (char)('a' + (number % 26));
	}
	name[0] = '.';
	name[1] = 't';
	name[2] = 'm';
	return (name);
}

int	handle_eof(char *input, int f, char *f_name)
{
	if (!input)
	{
		close(f);
		open(f_name, O_TRUNC);
		ft_put_err("bash: warning: here-document "
			"at line 1 delimited by end-of-file\n");
		return (1);
	}
	return (0);
}

void	here_read(char *delim, int has_quotes, int f, char *f_name)
{
	char	*input;
	char	*to_free;

	input = readline("> ");
	if (handle_eof(input, f, f_name))
		return ;
	if (!has_quotes)
		ft_substitution_heredoc(&input);
	while (input)
	{
		if (ft_strcmp(delim, input) == 0)
		{
			free(input);
			break ;
		}
		to_free = input;
		input = ft_strjoin(input, "\n");
		free(to_free);
		ft_putstr_fd(input, f);
		free(input);
		input = readline("> ");
		if (handle_eof(input, f, f_name))
			return ;
	}
}

int	here_doc_fd(char *delim)
{
	int		f;
	char	*file_name;
	int		has_quotes;

	has_quotes = 0;
	if (is_quotes(delim))
	{
		has_quotes = 1;
		cpy_unquote(delim, delim);
	}
	file_name = get_random_name();
	f = open(file_name, O_CREAT | O_EXCL | O_RDWR, 0644);
	if (f == -1)
		process_err("fatal: resource access error");
	here_read(delim, has_quotes, f, file_name);
	close(f);
	f = open(file_name, O_RDONLY);
	if (f == -1)
		process_err("fatal: resource access error");
	unlink(file_name);
	free(file_name);
	return (f);
}
