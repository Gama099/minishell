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
    // Check if it starts with '/' for absolute paths
    if (token[0] != '/' && token[0] != '.') {
        return 0; // Not a valid path
        printf("%c\n", token[0]);
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

// int is_env_var(char *token)
// {
//     if (!token || token[0] != '$')
//         return (0);
//     return(1);
// }

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
// iterate through list and only difind that it type

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

void	skip_token(t_tokens **list, t_tokens *current, t_tokens *prev)
{
	t_tokens *tmp = current;
	if (prev)
	{
		tmp = current;
		current = current->next;
		prev->next = current;
		free(tmp);
	}
	else
	{
		tmp = current;
		current = current->next;
		free(tmp);
		*list = current;
	}
}

void    parser(t_tokens **list)
{
    t_tokens    *current;
	t_tokens	*prev;
	int 		skip_flag;

	skip_flag = 0;
	prev = NULL;
    current = *list;
    while (current)
    {
		// printf("[%s]---[%d]\n", current->token, is_spaces(current->token));
		// printf("adress [%p]\n", current);
        if (!is_spaces(current->token))
		{
			t_tokens *tmp = current;
			if (prev){
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
        else if (!ft_strncmp(current->token, "|", ft_strlen(current->token)) && !current->qoute_type){
            current->tokenType = "pipe";
            //calling the function again so it should check if after pipe there's a command
            parser(&current->next);
            return ;
        }
        /*else if(is_env_var(current->token))
        {
            current->tokenType = "env_var";
        }*/
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
		// else if (!is_spaces(current->token))
		// {
		// 	t_tokens *tmp = current;
		// 	if (prev){
		// 		tmp = current;
		// 		current = current->next;
		// 		prev->next = current;
		// 		free(tmp);
		// 	}
		// 	else
		// 	{
		// 		tmp = current;
		// 		current = current->next;
		// 		free(tmp);
		// 		*list = current;
		// 	}
		// }
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
