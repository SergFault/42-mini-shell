/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:22:20 by eshana            #+#    #+#             */
/*   Updated: 2022/03/01 19:00:45 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_err(const char *str)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, str, ft_strlen(str));
}

void	ft_put_err_cmd(const char *cmd, const char *str)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void	ft_put_err_sh_cmd(const char *cmd, const char *str)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}
