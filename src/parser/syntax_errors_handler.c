#include "../../includes/minishell.h"

/*
Unmatched Quotes:
No specific test cases listed, but any command with unmatched single (') or double (") quotes should produce a syntax error.
Consecutive Meta-characters:
> > (double output redirection)
< < (double input redirection)
>> >> >> >> (multiple output redirections)
<< << (double heredoc)
>>> (multiple output redirections)
||||| (multiple logical ORs)
&&&&& (multiple logical ANDs)
;; (double semicolon)
; ; ; (multiple semicolons)
Invalid Redirection Syntax:
> < (output followed by input redirection)
<> (invalid combination of input and output redirection)
>>|>< (invalid combination of output redirection and pipe)
Empty Commands:
$> \n (just a newline)
$> [que des espaces] (only spaces)
$> [que des tabulations] (only tabs)
$> : (colon alone)
Invalid Command Structure:
$> | (pipe with no command)
$> | hola (pipe followed by a command)
$> || (logical OR with no command)
$> && (logical AND with no command)
$> ; (semicolon with no command)
$> ( ( ) ) (unmatched parentheses)
Invalid Identifiers:
$> - (dash alone)
$> ! (exclamation mark alone)
$> \\ (backslash alone)
$> \\\\ (multiple backslashes)
Heredoc Syntax:
$> cat << (heredoc without a delimiter)
$> << hola (heredoc with no closing delimiter)
$> <<<<< bonjour (multiple less-than signs)
Invalid Options:
$> ls -z (invalid option for a command)
Invalid Characters:
$> // (double slashes)
$> / (single slash)
$> /./../../../../.. (path traversal)
Invalid Command Structure with Special Characters:
$> | | | (multiple pipes)
$> ||||| (multiple logical ORs)
$> &&&&&&&&&&&&&& (multiple logical ANDs)
$> ;; (double semicolon)
$> () (empty parentheses)
$> ( ( ) ) (nested parentheses)

*/
     int check_unmatched_quotes(char *input);
     int check_consecutive_meta(char *input);
     int check_invalid_redirection(char *input);
     int check_empty_command(char *input);
     int check_invalid_command_structure(char *input);
     int check_invalid_identifiers(char *input);
     int check_heredoc_syntax(char *input);
     int check_invalid_options(char *input);
     int check_invalid_characters(char *input);
	 int check_special_character_structure(char *input);




int	handle_syntax_errors(const char *input)
{
	while (*input)
	{
		if (check_unmatched_quotes(input))
			printf("Syntax error: unexpected EOF while looking for matching `\"`\n");
		if (check_consecutive_meta(input))
			printf("Syntax error: consecutive meta characters found\n");
		if (check_invalid_redirection(input))
			printf("Syntax error: invalid redirection\n");
		if (check_empty_command(input))
			printf("Syntax error: empty command\n");
		if (check_invalid_command_structure(input))
			printf("Syntax error: invalid command structure\n");
		if (check_invalid_identifiers(input))
			printf("Syntax error: invalid identifiers\n");
		if (check_heredoc_syntax(input))
			printf("Syntax error: invalid heredoc syntax\n");
		if (check_invalid_options(input))
			printf("Syntax error: invalid options\n");
		if (check_invalid_characters(input))
			printf("Syntax error: invalid characters found\n");
		if (check_special_character_structure(input))
			printf("Syntax error: invalid special character structure\n");
		input++;
	}
}
