/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_all_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:21:04 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/14 02:29:56 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_all_files(void)
{
	struct dirent	*dp;
//	char			*path;
	DIR				*dir;

	dir = opendir(".");
	if (!dir)
		return ;
	dp = readdir(dir);
	while (dp != NULL)
	{
		if (ft_strncmp(dp->d_name, ".tm", 3) == 0)
		{
//		path = ft_strjoin("./temp/", dp->d_name);
			unlink(dp->d_name);
//		free(path);
		}
		dp = readdir(dir);
	}
	closedir(dir);
}
