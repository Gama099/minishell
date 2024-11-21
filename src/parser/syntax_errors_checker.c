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

int	handle_syntax_errors(t_tokens *tokens)
{
	t_tokens	*start;

	if (!tokens)
		return (1);
	start = tokens;
	while (tokens)
	{
		//1. input must not start with special operattea "with fries"
		if (tokens == start && (!ft_strcmps(tokens->tokenType, "pipe"))){
			printf("syntax error near unexpected token `%s'\n", tokens->token);
			return (1);
		}
		//last node
		else if (tokens->next == NULL &&
			(!ft_strcmps(tokens->tokenType, "pipe") ||
			!ft_strcmps(tokens->tokenType, "output") ||
			!ft_strcmps(tokens->tokenType, "input") ||
			!ft_strcmps(tokens->tokenType, "append") ||
			!ft_strcmps(tokens->tokenType, "herdoc")))
		{
			printf("syntax error near unexpected token `newline'\n");
			return (1);
		}
		// 2. Consecutive Special Operators Are Not Allowed
		// "I'd like, um, um, a burger."
		else if ((!ft_strcmps(tokens->tokenType, "pipe") && !ft_strcmps(tokens->next->tokenType, "output")) ||
				(!ft_strcmps(tokens->tokenType, "pipe") && !ft_strcmps(tokens->next->tokenType, "input")) ||
				(!ft_strcmps(tokens->tokenType, "pipe") && !ft_strcmps(tokens->next->tokenType, "append")) ||
				(!ft_strcmps(tokens->tokenType, "pipe") && !ft_strcmps(tokens->next->tokenType, "herdoc")) ||

				(!ft_strcmps(tokens->tokenType, "output") && !ft_strcmps(tokens->next->tokenType, "input")) ||
				(!ft_strcmps(tokens->tokenType, "output") && !ft_strcmps(tokens->next->tokenType, "append")) ||
				(!ft_strcmps(tokens->tokenType, "output") && !ft_strcmps(tokens->next->tokenType, "herdoc")) ||
				(!ft_strcmps(tokens->tokenType, "output") && !ft_strcmps(tokens->next->tokenType, "pipe")) ||

				(!ft_strcmps(tokens->tokenType, "input") && !ft_strcmps(tokens->next->tokenType, "output")) ||
				(!ft_strcmps(tokens->tokenType, "input") && !ft_strcmps(tokens->next->tokenType, "append")) ||
				(!ft_strcmps(tokens->tokenType, "input") && !ft_strcmps(tokens->next->tokenType, "herdoc")) ||
				(!ft_strcmps(tokens->tokenType, "input") && !ft_strcmps(tokens->next->tokenType, "pipe")) ||

				(!ft_strcmps(tokens->tokenType, "append") && !ft_strcmps(tokens->next->tokenType, "output")) ||
				(!ft_strcmps(tokens->tokenType, "append") && !ft_strcmps(tokens->next->tokenType, "input")) ||
				(!ft_strcmps(tokens->tokenType, "append") && !ft_strcmps(tokens->next->tokenType, "herdoc")) ||
				(!ft_strcmps(tokens->tokenType, "append") && !ft_strcmps(tokens->next->tokenType, "pipe")) ||

				(!ft_strcmps(tokens->tokenType, "herdoc") && !ft_strcmps(tokens->next->tokenType, "output")) ||
				(!ft_strcmps(tokens->tokenType, "herdoc") && !ft_strcmps(tokens->next->tokenType, "input")) ||
				(!ft_strcmps(tokens->tokenType, "herdoc") && !ft_strcmps(tokens->next->tokenType, "append")) ||
				(!ft_strcmps(tokens->tokenType, "herdoc") && !ft_strcmps(tokens->next->tokenType, "pipe")))
				{
					printf("syntax error near unexpected token `%s'\n", tokens->next->token);
					return (1);
				}
		tokens = tokens->next;
	}
	return (0);
}
