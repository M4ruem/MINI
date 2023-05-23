SRC = ./sources/main.c \
	./sources/builtins/cd.c ./sources/builtins/echo.c ./sources/builtins/error.c ./sources/builtins/exit.c \
	./sources/builtins/export.c ./sources/builtins/signals.c ./sources/builtins/unset1.c ./sources/builtins/unset2.c \
	./sources/env/env_in_list.c ./sources/env/env_lst_utils1.c ./sources/env/env_lst_utils2.c ./sources/env/env_replace_list.c \
	./sources/env/env_replace_str.c ./sources/exec/exec_one_cmd.c ./sources/exec/exec_path_fct.c ./sources/exec/execution_one.c \
	./sources/exec/execution_two.c ./sources/parsing/parsing_redir.c ./sources/parsing/parsing.c ./sources/parsing/parsing2.c \
	./sources/parsing/rm_quote.c ./sources/utils/cmd_lst_utils1.c ./sources/utils/cmd_lst_utils2.c ./sources/utils/ft_utils.c \
	./sources/utils/ft_utils2.c ./sources/utils/ft_utils3.c ./sources/utils/ft_utils4.c

OBJ = $(patsubst ./sources/%.c, .object/%.o, $(SRC))
INC = include/minishell.h

DIR_OBJ = .object
DIR_INC = include

CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline

NAME = minishell

all: $(NAME)

re: fclean all

clean:
	rm -rf $(DIR_OBJ)

fclean: clean
	rm -f $(NAME)

$(NAME): $(OBJ) | $(DIR_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(DIR_OBJ)/%.o: ./sources/%.c $(INC) Makefile | $(DIR_OBJ)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(DIR_INC)

$(DIR_OBJ):
	mkdir -p $(DIR_OBJ)

.PHONY: all re clean fclean
