/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:22:20 by eshana            #+#    #+#             */
/*   Updated: 2022/02/08 11:28:19 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_err(const char *str)
{
	write(2, "minishell:", ft_strlen("minishell:"));
	write(2, str, ft_strlen(str));
}
