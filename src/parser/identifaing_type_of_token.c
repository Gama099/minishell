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
    char	*iter;

	if (!token || !ft_strlen(token))
        return 0;
	iter = token;
    // Check if it starts with '/' for absolute paths
    if (token[0] != '/' && token[0] != '.') {
        return 0; // Not a valid path
    }
    while (*iter)
    {
        if (!(ft_isalnum(*iter) || *iter == '/' || *iter == '.' || *iter == '_'
			|| *iter == '-' || *iter == ' '))
			return 0;
        iter++;
    }
    return 1;

}

int	is_spaces(char *str)
{
	while (*str)
	{
		if (*str == ' ' || (*str >= '\r' && *str <='\t'))
			str++;
		else
			return (1);
	}
	return (0);
}

static int checkcommand(char *token)
{
    if (!is_word(token) && !is_path(token)){
            //printf("entre valid command\n");
            //exit(1);
			return (0);
    }
    else
        return(1);
}

void    parser(t_tokens **list)
{
    t_tokens    *current;
	t_tokens	*prev;
	int 		skip_flag;
	t_tokens 	*tmp;

	skip_flag = 0;
	prev = NULL;
    current = *list;
    while (current)
    {
        if (!is_spaces(current->token))
		{
			tmp = current;
			if (prev)
			{
				tmp = current;
				current = current->next;
				prev->next = current;
				free(tmp);
				if (current == NULL)
					break;
				skip_flag = 1;
			}
			else
			{
				tmp = current;
				current = current->next;
				free(tmp);
				*list = current;
				if (*list == NULL)
					break;
				skip_flag = 1;
			}
		}
        else if (current == *list && (checkcommand(current->token)))
            current->tokenType = "command";
        else if (!ft_strncmp(current->token, "|", ft_strlen(current->token)) && !current->qoute_type)
		{
            current->tokenType = "pipe";
            parser(&current->next);
            return ;
        }
        else if (!ft_strncmp(current->token, ">", ft_strlen(current->token)) && !current->qoute_type)
        {
            current->tokenType = "output";
			if (current->next && !is_operator(current->next->token))
            {
				prev = current;
                current = current->next;
                current->tokenType = "file";
            }
        }
        else if (!ft_strncmp(current->token, "<", ft_strlen(current->token)) && !current->qoute_type)
        {
            current->tokenType = "input";
            if (current->next && !is_operator(current->next->token))
            {
				prev = current;
                current = current->next;
                current->tokenType = "file";
            }
        }
        else if (!ft_strncmp(current->token, ">>", ft_strlen(current->token)) && !current->qoute_type)
        {
            current->tokenType = "appaned";
            if (current->next && !is_operator(current->next->token))
            {
				prev = current;
                current = current->next;
                current->tokenType = "file";
            }
        }
		else if (!ft_strncmp(current->token, "<<", ft_strlen(current->token)) && !current->qoute_type)
		{
			current->tokenType = "herdoc";
			if (current->next && !is_operator(current->next->token))
			{
				prev = current;
				current = current->next;
				current->tokenType = "file";
			}
		}
        else
            current->tokenType = "argurment";
        if (!skip_flag)
		{
			prev = current;
			current = current->next;
		}
		skip_flag = 0;
    }
}
