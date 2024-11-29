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

int	is_special_operator(char *tokentype)
{
    return (!ft_strcmps(tokentype, "output") ||
            !ft_strcmps(tokentype, "input") ||
            !ft_strcmps(tokentype, "appaned") ||
            !ft_strcmps(tokentype, "herdoc"));
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

	if (!tokens)
		return (0);
	start = tokens;
	while (tokens)
	{
		if (tokens == start && !ft_strcmps(tokens->tokentype, "pipe"))
		{
			ft_putstr_fd("syntax error near unexpected token ", 2);
			ft_putendl_fd(tokens->token, 2);
			return (2);
		}
		else if (!tokens->next && is_special_operator(tokens->tokentype))
			return (err_msg("syntax error near unexpected token`newline' ", NULL, NULL), 2);
		else if (is_special_operator(tokens->tokentype) && is_special_operator(tokens->next->tokentype))
		{
			ft_putstr_fd("syntax error near unexpected token ", 2);
			ft_putendl_fd(tokens->next->token, 2);
			return (2);
		}
		tokens = tokens->next;
	}
	return (0);
}
