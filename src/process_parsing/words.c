/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:47:57 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/02 17:52:23 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_word	*cut_word(int s_pos, int c_pos, char *line)
{
	char	*word_str;
	t_word	*word;

	word_str = malloc(sizeof (char) * (c_pos - s_pos + 1));
	word = malloc(sizeof(t_list));
	fatal_err_if((!word_str || !word), NULL);
	word_str[c_pos - s_pos] = '\0';
	ft_strncpy(word_str, line + s_pos, c_pos - s_pos);
	word->val = word_str;
	word->t = NONE;
	return (word);
}

t_list	*get_words(char *line)
{
	t_list	*words_lst;
	t_word	*word;
	int		len;
	int		s_pos;
	int		c_pos;

	words_lst = NULL;
	len = ft_strlen(line);
	c_pos = 0;
	while (c_pos < len)
	{
		while (c_pos < len && line[c_pos] == ' ')
			c_pos++;
		if (c_pos >= len)
			break ;
		s_pos = c_pos;
		if (line[c_pos] == '>' || line[c_pos] == '<')
			skip_redir(line, &c_pos);
		else
			skip_arg(line, &c_pos);
		word = cut_word(s_pos, c_pos, line);
		ft_lstadd_back(&words_lst, ft_lstnew(word));
	}
	return (words_lst);
}

t_list	*parse_words(char *line)
{
	t_list	*iter;
	t_list	*words_lst;

	words_lst = get_words(line);
	set_types(words_lst);
	iter = words_lst;
	while (iter)
	{
		ft_substitution(&(get_word(iter)->val));
		ft_unquote(&(get_word(iter)->val));
		iter = iter->next;
	}
	return (words_lst);
}

int	fill_words(t_list *cmd)
{
	while (cmd)
	{
		get_cmd(cmd)->element = parse_words(get_cmd(cmd)->cmd_line);
		cmd = cmd->next;
	}
	return (0);
}
