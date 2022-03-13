NAME = minishell
CPP	 = gcc
FLAGS = -Wall -Wextra -Werror
FLAGS += -MMD -MP
INCL_DIR = includes
SRCS_FILES 	= main.c process_signals/hook_up_sigactions.c \
				utils/ft_split.c utils/str_dup.c \
				utils/str_arr_size.c  utils/ft_strlen.c utils/str_insert.c\
				utils/ft_split_spaces.c utils/get_env_var.c\
				utils/ft_strlcpy.c utils/consider_empty.c\
				utils/ft_strnstr.c utils/ft_strchr.c utils/ft_substr.c\
				utils/ft_strcmp.c utils/ft_keycmp.c \
				utils/ft_putstr_fd.c \
				utils/ft_itoa.c \
				utils/mem_utils.c \
				utils/ft_is_digit.c \
				utils/ft_split_multiple_del.c \
				utils/have_first_last_char.c \
				utils/ft_strjoin.c utils/ft_strncmp.c utils/ft_strncpy.c\
				utils/error.c file_utils/here_doc.c utils/ft_split_pipes.c\
				process_parsing/parse.c \
				process_parsing/type_parser.c  \
				process_parsing/type_parser_helper.c \
				process_parsing/ft_unquote.c \
				process_parsing/checkers.c \
				process_parsing/checkers_2.c \
				process_parsing/is_quotes_open.c \
				process_parsing/parse_skippers.c \
				process_parsing/words.c \
				process_parsing/parse_environmets.c \
				process_parsing/prepare_for_split.c \
				process_launching/launch_commands.c \
				process_launching/launch_forked.c \
				process_launching/ft_wait_status.c \
				process_launching/ft_exe.c \
				process_parsing/validation.c \
				process_parsing/get_word_by_type.c \
				process_launching/x_bin_checker.c \
				builtins/cd.c builtins/echo.c builtins/pwd.c \
				builtins/env.c \
				builtins/export.c \
				builtins/export_helper.c \
				builtins/unset.c \
				builtins/exit.c \
				list_utils/ft_lstadd_front.c \
				list_utils/ft_lstadd_back.c \
				list_utils/word_getters.c \
				list_utils/ft_lstnew.c list_utils/getters.c \
				list_utils/ft_lstsize.c list_utils/ft_lstclear.c \
				utils/free_cmd_lst.c utils/free_str_arr.c \
				file_utils/setup_fd.c  file_utils/delete_all_files.c

SRCS_DIR = src/
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS = $(SRCS:.c=.o)

%.o:		%.c Makefile
						$(CPP) $(FLAGS) -I$(INCL_DIR) -c $< -o $@ -I../.brew/opt/readline/include

all:					$(NAME)

$(NAME):				$(OBJS)
						$(CPP) $(FLAGS) $(OBJS) -o $(NAME) -lreadline -L../.brew/opt/readline/lib

clean:
						@rm -rf $(OBJS)
						@rm -rf $(SRCS:.c=.d)

fclean:					clean
						@rm -f $(NAME)

re: 					fclean all

val:					all
						valgrind --leak-check=full \
								--suppressions=.valgrind-supression\
								--show-leak-kinds=all \
								--track-origins=yes \
								--verbose \
								--log-file=valgrind-out.txt \
								./$(NAME)

-include $(SRCS:.c=.d)

.PHONY: all clean fclean val re