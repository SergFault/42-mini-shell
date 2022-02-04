#ifndef MINI_SHELL_H
#define MINI_SHELL_H

/* unchecked */
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>

/* readline */
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/* signals */
#include <signal.h>

/* utils */
#include <stdlib.h>

# define PROMPT "original:"

int parse(void);
int launch_commands();

/* global env */
extern char **g_env;


/* signals */
int hook_signals();
void ft_exit();

/* common utils */
char	**ft_split(char const *s, char c);
int		consider_empty(char *str);
char	*ft_strdup(const char *s);
int		char_arr_size(char **char_arr);
int		parse_environment(char **env);
size_t		ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int launch_commands(char **raw_commands);
char	**ft_split_spaces(char const *s);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);

/*builtins*/

int		ft_cd(char *dest);
int		ft_pwd(void);
int		ft_env(void);

#endif
