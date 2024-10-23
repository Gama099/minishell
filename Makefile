CC = cc 
NAME = minishell
GFLAGS =-Wall -Wextra -Werror -Iincludes #-g3
HEADER = includes/minishell.h
SRC =	src/main.c \
		src/excution/excution.c \
		src/excution/execve_utils.c \
		src/excution/rediction.c \
		src/builtin/builtins_utils.c \
		src/builtin/cd.c \
		src/builtin/echo.c \
		src/builtin/env_utils.c \
		src/builtin/env.c \
		src/builtin/exit.c \
		src/builtin/export_utils.c \
		src/builtin/export.c \
		src/builtin/print_export.c \
		src/builtin/pwd.c \
		src/builtin/unset.c \
		src/utils/node.c \
		src/utils/split.c \
		src/utils/string_utils.c \
		src/utils/file_utils.c \
		src/utils/string_utils.c \
		src/systemcall.c \

		
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