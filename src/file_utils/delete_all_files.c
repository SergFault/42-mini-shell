#include <dirent.h>
#include "minishell.h"

void delete_all_files()
{
		struct dirent *dp;
		char *path;
		DIR *dir = opendir("./temp");

		if (!dir)
			return ;

		dp = readdir(dir);
		while (dp  != NULL)
		{
			path = ft_strjoin("./temp/", dp->d_name);
			unlink(path);
			free(path);
			dp = readdir(dir);
		}
		closedir(dir);
}