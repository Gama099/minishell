#include "../../includes/minishell.h"


int is_word(char *token)
{
    while (*token)
    {
        if (!ft_isalpha(*token))
            return 0;
        token++;
    }
    return 1;
}

int is_path(char *token)
{
    int		i;
    char	*iter;

    if (!token || !ft_strlen(token))
        return 0;
	i = 0;
	iter = token;
    if (token[0] != '/' && token[0] != '.')
		return (0);
    while (*iter)
    {
        if (!(ft_isalnum(*iter) || *iter == '/' || *iter == '.' || *iter == '_'
			|| *iter == '-' || *iter == ' '))
			return 0;
        iter++;
    }
    return 1;

}

int checkcommand(char *token)
{
    if (!is_word(token) && !is_path(token))
			return (0);
    else
        return(1);
}
