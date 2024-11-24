#include "../../includes/minishell.h"

int ft_strcmps(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
        if (*s1 != *s2)
			return (unsigned char)(*s1) - (unsigned char)(*s2);
        s1++;
        s2++;
    }
    return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

int	is_special_operator(char *tokenType)
{
    return (!ft_strcmps(tokenType, "pipe") ||
            !ft_strcmps(tokenType, "output") ||
            !ft_strcmps(tokenType, "input") ||
            !ft_strcmps(tokenType, "appaned") ||
            !ft_strcmps(tokenType, "herdoc"));
}

int	is_operator(char *token)
{
    return (!ft_strcmps(token, "|") ||
            !ft_strcmps(token, ">") ||
            !ft_strcmps(token, "<") ||
            !ft_strcmps(token, ">>") ||
            !ft_strcmps(token, "<<"));
}

int	handle_syntax_errors(t_tokens *tokens)
{
	t_tokens	*start;
	int			herdoc;

	herdoc = 16;
	if (!tokens)
		return (1);
	start = tokens;
	while (tokens)
	{
		if (tokens == start && !ft_strcmps(tokens->tokenType, "pipe"))
			return (printf("syntax error near unexpected token `%s'\n", tokens->token) ,2);
		else if (!tokens->next && is_special_operator(tokens->tokenType))
			return (printf("syntax error near unexpected token `newline'\n"), 2);
		else if (is_special_operator(tokens->tokenType) && is_special_operator(tokens->next->tokenType))
			return (printf("syntax error near unexpected token `%s'\n", tokens->next->token), 2);
		else if (is_special_operator(tokens->tokenType) && ft_strcmps(tokens->next->tokenType, "file"))
			return (printf("syntax error near unexpected token `%s'\n", tokens->next->token), 2);
		tokens = tokens->next;
	}
	return (0);
}
