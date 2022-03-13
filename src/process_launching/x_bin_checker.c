/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_bin_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:43:50 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/07 12:54:34 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*make_path(char *begin, char *end)
{
	char	*temp;
	char	*full;

	temp = ft_strjoin(begin, "/");
	full = ft_strjoin(temp, end);
	free(temp);
	return (full);
}

static int	check_file_exists(char *path)
{
	char	*var;

	var = get_env_var(g_data.env, "PATH");
	if (access(path, F_OK) == 0)
	{
		return (BIN_SUCCEED);
	}
	if (ft_strlen(var))
	{
		free(var);
		return (BIN_NOT_FOUND);
	}
	free(var);
	return (FILE_NOT_FOUND);
}

static int	check_file_perms(char *path)
{
	struct stat	buf;

	buf.st_mode = 0;
	stat(path, &buf);
	if (S_ISDIR(buf.st_mode))
		return (BIN_IS_DIR);
	if (access(path, X_OK) == 0)
		return (BIN_SUCCEED);
	if (access(path, F_OK) != 0)
		return (FILE_NOT_FOUND);
	return (BIN_PERM_ERR);
}

static int	check_bin_name(const char *bin_name, char **assembled_path)
{
	int	i;

	i = 0;
	while (bin_name[i])
	{
		if (bin_name[i] == '/')
		{
			free(*assembled_path);
			*assembled_path = ft_strdup(bin_name);
			return (1);
		}
		i++;
	}
	return (0);
}

int	assemble_path(char *bin_name, char **paths, char **assembled_path)
{
	int	pos;
	int	found;
	int	check;

	found = 0;
	*assembled_path = ft_strdup("");
	check = check_bin_name(bin_name, assembled_path);
	pos = -1;
	while (!check && paths && paths[++pos])
	{
		free(*assembled_path);
		*assembled_path = make_path(paths[pos], bin_name);
		if (check_file_exists(*assembled_path) == BIN_SUCCEED)
		{
			found = 1;
			break ;
		}
	}
	if (found == 0 && check == 0)
		return (check_file_exists(*assembled_path));
	return (check_file_perms(*assembled_path));
}
