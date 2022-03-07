/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:53:26 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/07 22:53:26 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_insert(char *big, char *pos, char *lit)
{
	char	*str1;
	char	*str3;
	char	*temp;

	str3 = ft_strdup(pos);
	*pos = '\0';
	str1 = ft_strdup(big);
	temp = str1;
	str1 = ft_strjoin(str1, lit);
	free(temp);
	temp = str1;
	str1 = ft_strjoin(str1, str3);
	free(temp);
	free(big);
	return (str1);
}
