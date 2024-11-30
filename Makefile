CC = cc
NAME = minishell
CFLAGS = -g3 -Wall -Wextra -Werror
HEADER = minishell.h
INC = includes
SRC =	src/main.c \
		src/excution/excution.c \
		src/excution/herdoc.c \
		src/excution/execve_utils.c \
		src/excution/execve_utils_2.c \
		src/excution/rediction.c \
		src/excution/excution_pipe.c \
		src/excution/ambiguous.c \
		src/excution/herdoc_utils.c \
		src/excution/ft_shell.c \
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
		src/builtin/redirection_builtins.c \
		src/builtin/redirection_utils.c \
		src/utils/node.c \
		src/utils/node_utils.c \
		src/utils/itoa.c \
		src/utils/atoi.c \
		src/utils/split.c \
		src/utils/string_utils.c \
		src/utils/string_utils_2.c \
		src/utils/string_utils_3.c \
		src/systemcall.c \
		src/error_utils.c \
		src/signals.c \
		src/parse/expand_norm.c \
		src/parse/trim.c \
		src/parse/to_strcut.c \
		src/parse/syntax_error.c \
		src/parse/qoute.c \
		src/parse/expand_variables.c \
		src/parse/id_token.c \
		src/parse/id_token_p.c \
		src/parse/join_sybling_tokens.c \
		src/parse/tokenaze.c \
		src/parse/tokenaze_p.c \
		src/parse/tokenaze_pp.c \
		src/parse/tokenaze_var.c \
		src/parse/mem.c \
		src/parse/to_strcut_p.c \
		src/parse/syntax_error_p.c \
		src/parse/tokenaze_uti.c \

OBJECT = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJECT)
	$(CC) $(CFLAGS) -I$(INC) $(OBJECT)   -lreadline -o $@

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I$(INC) -c $? -o $@

clean:
	rm -f $(OBJECT)

fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY : clean fclean re all
