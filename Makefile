NAME		= mini_shell
CC			= clang
FLAGS		= -g #-Wextra -Wall -Werror
INCLUDES 	= includes
HDR			= ${INCLUDES}/mini_shell.h
SRC_DIR		= src/
SRC_FILES 	= main.c /process_signals/hook_up_sigactions.c \
				utils/ft_split.c utils/str_dup.c \
				utils/char_arr_size.c  utils/ft_strlen.c \
				utils/ft_split_spaces.c utils/get_env_var.c\
				utils/ft_strlcpy.c utils/consider_empty.c\
				utils/ft_strnstr.c utils/ft_strchr.c \
				utils/ft_strjoin.c \
				process_parsing/parse.c \
				process_launching/launch_commands.c \
				process_launching/x_bin_checker.c \
				builtins/cd.c builtins/echo.c builtins/pwd.c \
				builtins/env.c builtins/export.c builtins/unset.c \
				builtins/exit.c \
				list_utils/ft_lstadd_front.c list_utils/ft_lstadd_back.c \
				list_utils/ft_lstnew.c list_utils/getters.c \
				list_utils/ft_lstsize.c
SRC			= $(addprefix ${SRC_DIR}, ${SRC_FILES})
OBJ			= ${SRC:.c=.o}

%.o: %.c ${HDR} Makefile
	$(CC) -c $(FLAGS) -I$(INCLUDES) $< -o $@

all:		$(NAME)

$(NAME):	$(OBJ)
				$(CC) $(FLAGS) -o $@ $^ -lreadline

clean:
				rm -f ${OBJ}
				rm -f ${OBJ}

fclean:		clean
				rm -f ${NAME}

re:			fclean all

val:
			valgrind --leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes --verbose --log-file=valgrind-out.txt ./${NAME}

.PHONY:		re all clean fclean val