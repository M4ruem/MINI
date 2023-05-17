SOURCES = main.c parsing.c parsing2.c parsing_redir.c env_replace_list.c \
		  env_replace_str.c env_in_list.c error.c cmd_lst_utils1.c cmd_lst_utils2.c \
		  env_lst_utils1.c env_lst_utils2.c ft_utils.c ft_utils2.c ft_utils3.c \
		  ft_utils4.c execution_one.c execution_two.c exec_path_fct.c exec_one_cmd.c \
		  rm_quote.c echo.c cd.c exit.c export.c unset1.c unset2.c signals.c

OBJETS = $(SOURCES:.c=.o)
INCLUDES = minishell.h

DIR_SRC = sources
DIR_OBJ = .object
DIR_INC = include

SRC := $(addprefix $(DIR_SRC)/,$(SOURCES))
OBJ := $(addprefix $(DIR_OBJ)/,$(OBJETS))
INC := $(addprefix $(DIR_INC)/,$(INCLUDES))

CC := gcc
CFLAGS := -Wall -Werror -Wextra
LDFLAGS := -L /usr/include -lreadline -L $(shell brew --prefix readline)/lib
CPPFLAGS := -I $(shell brew --prefix readline)/include
NAME := minishell

all : $(NAME)
re : fclean all
clean :
	rm -rf $(DIR_OBJ)
fclean : clean
	rm -rf minishell

$(NAME) : $(OBJ) | $(DIR_BIN)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o $(NAME) -lreadline
$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c $(INC) Makefile | $(DIR_OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ -I $(DIR_INC)
$(DIR_OBJ) :
	mkdir -p $(DIR_OBJ)

.PHONY : all bonus re clean fclean
