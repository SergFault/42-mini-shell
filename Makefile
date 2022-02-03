NAME		= mini_shell
CC			= clang
FLAGS		= -g #-Wextra -Wall -Werror
INCLUDES 	= includes/
HDR			= ${INCLUDES}mini_shell.h
SRC_DIR		= src/
SRC_FILES 	= main.c /process_signals/hook_up_sigactions.c \
				utils/exit.c utils/ft_split.c utils/str_dup.c \
				utils/char_arr_size.c  utils/ft_strlen.c \
				utils/ft_split_spaces.c \
				utils/ft_strlcpy.c utils/consider_empty.c\
				process_parsing/parse.c \
				process_launching/launch_commands.c
SRC			= $(addprefix ${SRC_DIR}, ${SRC_FILES})
OBJ			= ${SRC:.c=.o}

%.o : 		%.c ${HDR} Makefile
				$(CC) $(FLAGS) -I$(INCLUDES) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJ)
				$(CC) $(FLAGS) -o $@ $^ -lreadline

clean:
				rm -f ${OBJ}
				rm -f ${OBJ}

fclean:		clean
				rm -f ${NAME}

re:			fclean all

.PHONY:		re all clean fclean