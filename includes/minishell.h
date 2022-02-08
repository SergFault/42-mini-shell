#ifndef MINI_SHELL_H
#define MINI_SHELL_H

/* unchecked */
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

/* readline */
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/* signals */
#include <signal.h>

/* utils */
#include <stdlib.h>

# define PROMPT "original:"
# define BIN_SUCCEED 0
# define BIN_PERM_ERR 1
# define BIN_NOT_FOUND 2

enum type{
	NONE, //default set
	ARG, //word
	FILE_IN_OP, //word == '<'
	HERE_DOC_OP, // word == '<<'
	FILE_OUT_OP, //word == '>'
	FILE_OUT_APPEND_OP, //word == '>>'
	IN_FILE, // word following '<'
	LIM, // word following '<<'
	OUT_FILE, // word following '>'
	FILE_OUT_APPEND // word following '>>'
};

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

typedef struct s_command{
	char *cmd_line;
	t_list *element;
} t_command;

typedef struct s_word{
	char *val;
	enum type t;
} t_word;

int parse(void);
int launch_commands();

/* global env */
extern char **g_env;


/* signals */
int hook_signals();

/* common utils */
char	**ft_split(char const *s, char c);
int		consider_empty(char *str);
char	*ft_strdup(const char *s);
int		ft_str_arr_size(char **char_arr);
int		parse_environment(char **env);
size_t		ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int 	launch_commands(t_list **commands);
char	**ft_split_spaces(char const *s);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*get_env_var(char **var_arr, const char *key);
char	*ft_strjoin(char const *s1, char const *s2);
void    ft_put_err(const char *str);
int		ft_strcmp(const char *s1, const char *s2);

/* launching utils */
int	assemble_path(char *bin_name, char **paths, char **assembled_path);

/*builtins*/
int		ft_cd(char **argv);
int		ft_pwd(void);
int		ft_env(void);
int		ft_exit(char **params, t_list *cmd_to_free);
int		ft_echo(char **argv);

/* parse */
t_list *parse_input(char *input);
int		set_types(t_list *elements);
int is_file_in_op(t_list *pList);
int is_here_doc(t_list *pList);
int is_file_out_append(t_list *pList);
int is_file_out_op(t_list *pList);
int is_file_out_append_op(t_list *pList);
int is_in_file(t_list *pList);
int is_lim(t_list *pList);
int is_out_file(t_list *pList);
int is_arg(t_list *pList);
t_word *get_word_by_type(t_list *cmd, enum type t);

/* list utils */
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void*));
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* dao */
t_command *get_cmd(t_list *lst);
t_word		*get_word(t_list *lst);
char **get_args(t_list *command);
char *get_word_str(t_list *lst);
enum type get_word_type(t_list *lst);

/* memutils */
void free_cmds(t_list **cmds);
void free_word(void* word);
void free_cmd(void* cmd);
void free_str_arr(char ** str_arr);
void free_all(t_list *cmds);

/* debug */
void print_word(t_list *word);
void print_cmds(t_list *cmd);

/* redirect */
int setup_fd(t_list *command);


#endif
