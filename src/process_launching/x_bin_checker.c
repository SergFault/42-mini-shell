
# include "../../includes/minishell.h"

static char *make_path(const char *begin, const char *end)
{
	char *temp;
	char *full;

	temp = ft_strjoin(begin, "/");
	full = ft_strjoin(temp, end);
	free(temp);
	return (full);
}

static int check_file_exists(char *path)
{
	if (access(path, F_OK) == 0)
	{
		return (BIN_SUCCEED);
	}
	return (BIN_NOT_FOUND);
}

static int check_file_perms(char *path)
{
	struct stat	buf;

	buf.st_mode = 0;
	stat(path, &buf);
	if (S_ISDIR(buf.st_mode))
		return (BIN_IS_DIR);
	if (access(path, X_OK) == 0)
	{
		return (BIN_SUCCEED);
	}
	return (BIN_PERM_ERR);
}

static int check_bin_name(const char *bin_name, char **assembled_path)
{
	int i;

	i = 0;
	while (bin_name[i])
	{
		if (bin_name[i] == '/')
		{
			*assembled_path = ft_strdup(bin_name);
			return (1);
		}
		i++;
	}
	return (0);
}

int assemble_path(char *bin_name, char **paths, char **assembled_path)
{
	int pos;
	int found;
	int check;

	found = 0;
	check = check_bin_name(bin_name, assembled_path);
	pos = -1;
	while (!check && paths && paths[++pos])
	{
		*assembled_path = make_path(paths[pos], bin_name);
		if (check_file_exists(*assembled_path) == BIN_SUCCEED)
		{
			found = 1;
			break;
		}
		free(*assembled_path);
	}
	if (found == 0 && check == 0)
		return (BIN_NOT_FOUND);
	if (check_file_perms(*assembled_path) == BIN_SUCCEED)
		return (BIN_SUCCEED);
	if (check_file_perms(*assembled_path) == BIN_IS_DIR)
		return (BIN_IS_DIR);
	return (BIN_PERM_ERR);
}