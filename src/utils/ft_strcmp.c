/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:59:47 by sergey            #+#    #+#             */
/*   Updated: 2022/02/19 05:49:23 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	len;
	//size_t len_s1;
	//size_t len_s2;

	len = ft_strlen(s1);
	/*len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 < len_s2)
		return (ft_strncmp(s1, s2, len_s1));
	return (ft_strncmp(s1, s2, len_s2));*/
	return (ft_strncmp(s1,s2, len)==0 && s2[len]==0);
}
