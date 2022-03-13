/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:25:56 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/13 13:41:04 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* unchecked */
# include <stddef.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>

/* readline */
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/* signals */
# include <signal.h>

/* utils */
# include <stdlib.h>
# include <dirent.h>
# include <fcntl.h>

# define PROMPT "minishell$ "
# define BIN_SUCCEED 0
# define BIN_PERM_ERR 1
# define BIN_NOT_FOUND 2
# define BIN_IS_DIR 3
# define FILE_NOT_FOUND 4

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

enum e_type{
	NONE,
	ARG,
	FILE_IN_OP,
	HERE_DOC_OP,
	FILE_OUT_OP,
	FILE_OUT_APPEND_OP,
	IN_FILE,
	LIM,
	OUT_FILE,
	FILE_OUT_APPEND
};

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

typedef struct s_command{
	char	*cmd_line;
	t_list	*element;
}				t_command;

typedef struct s_word{
	char		*val;
	enum e_type	t;
}				t_word;

/* global env */
//extern char **g_data.env;

typedef struct s_data
{
	char	**env;
	int		ret_val;
}	t_data;

extern t_data	g_data;

/* main */
int			launch_commands(t_list **commands);

/* signals */
void		hook_signals(void);
void		hook_signals_child(void);
void		reset_signals(void);
void		sig_handler2(int sig_no);
void		sig_handler(int sig_no);

/* common utils */
char		**ft_split(char const *s, char c);
int			consider_empty(char *str);
char		*ft_strdup(const char *s);
int			ft_str_arr_size(char **char_arr);
int			parse_environment(char **env);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		**ft_split_spaces(char const *s);
char		*ft_strnstr(const char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
char		*get_env_var(char **var_arr, char *key);
char		*ft_strjoin(char *s1, char *s2);
void		ft_put_err(const char *str);
void		ft_put_err_cmd(const char *cmd, const char *str);
void		ft_put_err_sh_cmd(const char *cmd, const char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_keycmp(const char *s1, const char *s2);
void		ft_putstr_fd(char *s, int fd);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strncpy(char *dest, char *src, unsigned int n);
char		**ft_split_multiple_del(char const *s, char *del);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
void		ft_free_exit_err(int status);
int			ft_is_digit(char ch);

/* simple checks*/
int			is_delim(char i);
int			have_file_in_op(t_list *commands_list);
int			have_first_last_char(char *string, char ch);
int			have_here_doc_cmds(t_list *commands_list);
int			have_lim_here_doc(t_list *commands_list);
int			have_file_in(t_list *commands_list);
int			have_any_out_redir_op(t_list *commands_list);
int			have_file_out(t_list *commands_list);

/* launching utils */
int			assemble_path(char *bin_name, char **paths, char **assembled_path);
void		ft_wait_status(void);
int			ft_exe(t_list *command, t_list *commands);
int			is_built_in(t_list *cmd_lst);
int			launch_built_in(t_list *command, t_list *cmd_list);
void		launch_forked(t_list *command_lst, int fd[2], int std_io[2],
				int cmd_count);
char		*get_path(char *raw_cmd, int *status);

/*builtins*/
int			ft_cd(char **argv);
int			ft_pwd(void);
int			ft_env(void);
int			ft_exit(char **params, t_list *cmd_to_free);
int			ft_echo(char **argv);
int			ft_export(char **argv);
int			ft_unset(char **argv);
int			ft_ltrs_undersc(char c);
int			ft_valid_name(const char *name);
int			ft_value_changed(char *name);
void		cut_key(char *key);
int			change_val(char *name, char *key, int *i);

/* parse */
t_list		*parse_input(char **input);
int			set_types(t_list *elements);
int			is_file_in_op(t_list *pList);
int			is_here_doc(t_list *pList);
int			is_file_out_append(t_list *pList);
int			is_file_out_op(t_list *pList);
int			is_file_out_append_op(t_list *pList);
int			is_in_file(t_list *pList);
int			is_lim(t_list *pList);
int			is_out_file(t_list *pList);
int			is_arg(t_list *pList);
t_word		*get_word_by_type(t_list *cmd, enum e_type t);
char		*get_first_arg_word_str_ref(t_list *cmd);
int			here_doc_fd(char *delim);
void		delete_all_files(void);
int			is_quotes_open(char *str);
void		change_quote_flags(int q_flags[2], const char *ch);
char		*str_insert(char *big, char *pos, char *lit);
void		ft_substitution(char **str_p);
void		ft_unquote(char **str_p);
void		skip_arg(char *line, int *c_pos);
void		skip_redir(char *line, int *pos);
int			is_quotes(const char *str);
int			cpy_unquote(char *src, char *dst);
char		**ft_split_quotes(char const *s);
int			is_inconsiderable(char ch);
int			fill_words(t_list *cmd);
void		ft_put_err_simple(const char *str);
int			validate_in(char *input);
int			parse(void);
int			validate_wrds(t_list *l_cmds);

/* list utils */
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);
void		ft_lstclear(t_list **lst, void (*del)(void*));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		**ft_split_pipes(char const *s);

/* dao */
t_command	*get_cmd(t_list *lst);
t_word		*get_word(t_list *lst);
char		**get_args(t_list *command);
char		*get_word_str(t_list *lst);
enum e_type	get_word_type(t_list *lst);

/* memutils */
void		free_cmds(t_list **cmds);
void		free_word(void *word);
void		free_cmd(void *cmd);
void		free_str_arr(char **str_arr);
void		free_all(t_list *cmds);
void		free_all_but_hist(t_list *cmds);
void		fatal_err_if(int bool, t_list *cmds_to_free);

/* redirect */
int			setup_fd(t_list *command, int pInt[2]);

#endif
