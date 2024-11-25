CC = cc
NAME = minishell
CFLAGS =-g3 #-Wall -Wextra -Werror
HEADER = minishell.h
INC = includes
SRC =	src/main.c \
		src/excution/excution.c \
		src/excution/herdoc.c \
		src/excution/execve_utils.c \
		src/excution/rediction.c \
		src/excution/excution_pipe.c \
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
		src/utils/atoi.c \
		src/utils/split.c \
		src/utils/string_utils.c \
		src/systemcall.c \
		src/error_utils.c \
		src/signals.c \
		src/parser/buffor_to_tokenazation.c \
		src/parser/check_qoutes_validation.c \
		src/parser/expand_variables.c \
		src/parser/identifaing_type_of_token.c \
		src/parser/to_struct.c \
		src/parser/trim_spaces_from_start_end.c \
		src/parser/while_loop_and_buffring.c \
		src/parser/join_sybling_tokens.c \
		src/parser/syntax_errors_checker.c \
		src/parser/toknaze_env_vars.c \
		src/memory/memory.c \

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
