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
    int i = 0;
    char    *iter = token;
    if (!token || !ft_strlen(token))
        return 0;
    // Check if it starts with '/' for absolute paths
    if (token[0] != '/' && token[0] != '.') {
        return 0; // Not a valid path
        printf("%c\n", token[0]);
    }
    while (*iter)
    {
        if (!(ft_isalnum(*iter) || *iter == '/' || *iter == '.' || *iter == '_' || *iter == '-' || *iter == ' '))
            return 0;
        iter++;
    }
    return 1;

}

int is_env_var(char *token)
{
    if (!token || token[0] != '$')
        return (0);
    return(1);
}

static int checkcommand(char *token)
{
    if (!is_word(token) && !is_path(token)){
            printf("entre valid command\n");
            exit(1);
    }
    else
        return(1);
}
// iterate through list and only difind that it type
void    parser(t_tokens **list)
{
    t_tokens    *current;

    current = *list;
    while (current)
    {
        //check if it a word or path
        if (current == *list && (checkcommand(current->token)))
            current->tokenType = "command";
        else if (!ft_strncmp(current->token, "|", ft_strlen(current->token))){
            current->tokenType = "pipe";
            //calling the function again so it should check if after pipe there's a command
            parser(&current->next);
            return ;
        }
        /*else if(is_env_var(current->token))
        {
            current->tokenType = "env_var";
        }*/
        else if (!ft_strncmp(current->token, ">", ft_strlen(current->token)))
        {
            current->tokenType = "output";
            if (current->next)
            {
                current = current->next;
                current->tokenType = "file";
            }
        }
        else if (!ft_strncmp(current->token, "<", ft_strlen(current->token)))
        {
            current->tokenType = "input";
            if (current->next)
            {
                current = current->next;
                current->tokenType = "file";
            }
        }
        else if (!ft_strncmp(current->token, ">>", ft_strlen(current->token)))
        {
            current->tokenType = "appaned";
            if (current->next)
            {
                current = current->next;
                current->tokenType = "file";
            }
        }
        else
            current->tokenType = "argurment";
        current = current->next;
    }
}
