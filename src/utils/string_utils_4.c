#include "../../includes/minishell.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}

char	*expand_herdoc(char *str)
{
	char		*tmp;
	t_tokens	*tokens;

	tmp = NULL;
	tokens = get_tokens(str, 0);
	expand_varibles(&tokens);
	while (tokens != NULL)
	{
		tmp = ft_strjoin(tmp, tokens->token);
		if (tokens->token != NULL)
			tmp = ft_strjoin(tmp, " ");
		tokens = tokens->next;
	}
	return (tmp);
}
