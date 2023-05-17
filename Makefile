NAME = minishell

CC = clang

LIBFT_PATH = libft/ --no-print-directory
LIBFT_NAME = libft/libft.a

CFLAGS = -Wall -Werror -Wextra -g 

SRCS		= 	./src/minishell.c ./src/builtins/builtins.c ./src/builtins/cd.c \
				./src/builtins/echo.c ./src/builtins/env.c ./src/builtins/exit.c \
				./src/builtins/export.c ./src/builtins/pwd.c ./src/builtins/unset.c \
				./src/exec/check_files.c ./src/exec/cmd_utils.c ./src/exec/double_join.c \
				./src/exec/error.c ./src/exec/exec.c ./src/exec/heredoc.c ./src/exec/redir.c \
				./src/exec/wait.c ./src/parser/check.c ./src/parser/token.c ./src/parser/token2.c \
				./src/parser/token3.c ./src/utils/display.c ./src/utils/env2.c ./src/utils/env3.c \
				./src/utils/envlist.c ./src/utils/error.c ./src/utils/signal.c ./src/utils/string.c \
				./src/utils/strlist.c ./src/utils/toklist.c 

OBJ = ${SRCS:.c=.o}

all: $(LIBFT_NAME) $(NAME)

bonus: $(LIBFT_NAME)

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJ)
	${CC}  $(OBJ) $(LIBFT_NAME) -lreadline -o ${NAME}

$(LIBFT_NAME):
	make -C $(LIBFT_PATH)

clean:
	make clean -C ./libft
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	rm -rf $(NAME)

re: fclean all

.PHONY:
	re all clean fclean
