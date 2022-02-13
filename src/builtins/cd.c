/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:25:47 by eshana            #+#    #+#             */
/*   Updated: 2022/02/09 01:06:01 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **argv)
{
	int	ret;

	if (argv[1])
		ret = chdir(argv[1]);
	if (!ret)
	{
		//rewrite PWD & OLDPWD
		return (0);
	}
	ft_put_err("minishell: cd: ");
	perror(argv[1]);
	return(errno);
}
