/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_all_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:21:04 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/07 19:23:37 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_all_files(void)
{
	struct dirent	*dp;
	char			*path;
	DIR				*dir;

	dir = opendir("./temp");
	if (!dir)
		return ;
	dp = readdir(dir);
	while (dp != NULL)
	{
		path = ft_strjoin("./temp/", dp->d_name);
		unlink(path);
		free(path);
		dp = readdir(dir);
	}
	closedir(dir);
}
