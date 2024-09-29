CC = cc 
NAME = minishell
GFLAGS =-Wall -Wextra -Werror #-g3
HEADER = includes/minishell.h
SRC =	src/main.c \
		src/excution/excution.c \
		src/excution/execve_utils.c \
		src/excution/rediction.c \
		src/excution/builtin/builtins_utils.c \
		src/excution/builtin/cd.c \
		src/excution/builtin/echo.c \
		src/excution/builtin/env.c \
		src/excution/builtin/exit.c \
		src/excution/builtin/export.c \
		src/excution/builtin/pwd.c \
		src/excution/builtin/unset.c \
		src/utils/node.c \
		src/utils/split.c \
		src/utils/string_utils.c \

		
OBJECT = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT) $(HEADER)
	$(CC) $(GFLAGS) $(OBJECT) -o $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECT)

fclean: clean
	rm -f $(NAME)
re: fclean all