#include "../../includes/minishell.h"

typedef struct s_tokenizer {
    char    *input;         // Original input string
    char    *current;       // Current position in input
    char    *token_start;   // Start of current token
    int     in_quotes;      // Are we inside quotes?
    char    quote_char;     // Current quote character (' or ")
	char	tmp_holder;		// Char to hold the char that will be nulled
    t_error last_error;     // Last error encountered
} t_tokenizer;

t_tokens	*tokenize_input(char *input)
{
	
}
