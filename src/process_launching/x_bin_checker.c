
# include "../../includes/mini_shell.h"

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
	if (access(path, X_OK) == 0)
	{
		return (BIN_SUCCEED);
	}
	return (BIN_PERM_ERR);
}


int assemble_path(char *bin_name, char **paths, char **assembled_path)
{
	int pos;
	int found;

	found = 0;
	pos = -1;
	while (paths && paths[++pos])
	{
		*assembled_path = make_path(paths[pos], bin_name);
		if (check_file_exists(*assembled_path) == BIN_SUCCEED)
		{
			found = 1;
			break;
		}
		free(*assembled_path);
	}
	if (found == 0)
		return (BIN_NOT_FOUND);
	if (check_file_perms(*assembled_path) == BIN_SUCCEED)
	{
		return (BIN_SUCCEED);
	}
	return (BIN_PERM_ERR);
}