NAME		= mini_shell
CC			= clang
FLAGS		= #-Wextra -Wall -Werror -g
INCLUDES 	= includes/
HDR			= ${INCLUDES}mini_shell.h
SRC_DIR		= src/
SRC_FILES 	= main.c /process_signals/hook_up_sigactions.c \
				utils/exit.c
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