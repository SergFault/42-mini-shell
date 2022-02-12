NAME		= minishell
CC			= clang
FLAGS		= -g #-Wextra -Wall -Werror
INCLUDES 	= includes
HDR			= ${INCLUDES}/minishell.h
SRC_DIR		= src/
SRC_FILES 	= main.c /process_signals/hook_up_sigactions.c \
				utils/ft_split.c utils/str_dup.c \
				utils/str_arr_size.c  utils/ft_strlen.c \
				utils/ft_split_spaces.c utils/get_env_var.c\
				utils/ft_strlcpy.c utils/consider_empty.c\
				utils/ft_strnstr.c utils/ft_strchr.c \
				utils/ft_strcmp.c utils/ft_putstr_fd.c \
				utils/ft_strjoin.c utils/ft_strncmp.c \
				utils/error.c \
				process_parsing/parse.c process_parsing/type_parser.c \
				process_launching/launch_commands.c \
				process_parsing/get_word_by_type.c \
				process_launching/x_bin_checker.c \
				builtins/cd.c builtins/echo.c builtins/pwd.c \
				builtins/env.c builtins/export.c builtins/unset.c \
				builtins/exit.c \
				list_utils/ft_lstadd_front.c list_utils/ft_lstadd_back.c \
				list_utils/ft_lstnew.c list_utils/getters.c \
				list_utils/ft_lstsize.c list_utils/ft_lstclear.c \
				utils/free_cmd_lst.c utils/free_str_arr.c \
				file_utils/setup_fd.c \
				debug/deb.c
SRC			= $(addprefix ${SRC_DIR}, ${SRC_FILES})
OBJ			= ${SRC:.c=.o}

%.o: %.c ${HDR} Makefile
	$(CC) -c $(FLAGS)  -I../.brew/opt/readline/include -I$(INCLUDES) $< -o $@

all:		$(NAME)

$(NAME):	$(OBJ)
				$(CC) $(FLAGS) -o $@ $^ -lreadline -L../.brew/opt/readline/lib

clean:
				rm -f ${OBJ}
				rm -f ${OBJ}

fclean:		clean
				rm -f ${NAME}

re:			fclean all

val:		$(NAME)
			valgrind \
			--suppressions=.valgrind-supression \
			--leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			--log-file=valgrind-out.txt \
			./${NAME}

.PHONY:		re all clean fclean val
