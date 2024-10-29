CC = cc
NAME = minishell
#GFLAGS =-Wall -Wextra -Werror -Iincludes -g3
HEADER = minishell.h
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
		src/utils/atoi.c \
		src/utils/split.c \
		src/utils/string_utils.c \
		src/utils/file_utils.c \
		src/systemcall.c \
		src/error_utils.c \
		src/parser/buffor_to_tokenazation.c \
		src/parser/check_qoutes_validation.c \
		src/parser/expand_variables.c \
		src/parser/identifaing_type_of_token.c \
		src/parser/to_struct.c \
		src/parser/trim_spaces_from_start_end.cc \
		src/parser/while_loop_and_buffring.c \

OBJECT = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT)
	$(CC) $(OBJECT) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC)  -c $< -o $@

clean:
	rm -f $(OBJECT)

fclean: clean
	rm -f $(NAME)
re: fclean all
