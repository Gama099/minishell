#include "../../includes/minishell.h"

void	creat_list(t_env_var **list, char *token)
{
	t_env_var	*env_var;
	t_env_var	*tmp;
	char		*tmp_env;

	env_var = malloc(sizeof(t_env_var));
	env_var->var = token;
	tmp_env = getenv(token);
	if (tmp_env == NULL)
		env_var->real_value = ft_strdup(" ");
	else
		env_var->real_value = ft_strdup(tmp_env);
	env_var->next = NULL;
	if (!*list)
		*list = env_var;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = env_var;
	}
}

int	count_evn_vars_len(t_env_var *list)
{
	int	count;

	count = 0;
	while (list)
	{
		count += ft_strlen(list->real_value);
		list = list->next;
	}
	return (count);
}
void	write_new_token(char *new_token, char *token_str, t_env_var *env_list);/*
{
	while (*token_str)
	{
		if (*token_str == '$')
		{
			printf("real_value = %s\n", env_list->real_value);
			strcpy(new_token, env_list->real_value);
			new_token = &new_token[ft_strlen(env_list->real_value)];
			printf("new_token = [%s]\n", new_token);
			token_str++;
			while ((ft_isalpha(*token_str)) || ft_isdigit(*token_str) || *token_str == '_')//u need to check for null!!!!!
				token_str++;
			env_list = env_list->next;
		}
		else
			*new_token++ = *token_str++;
	}
	*new_token = '\0';
}*/
/*
int	find_metachar(char *iter)
{
	while (*iter)
	{
		if (*iter == '$'){
			return (1);
		}
		iter++;
	}
	return (0);
}


int	is_meta_char(char character)
{
	if (character == '$' || character == '>' || character == '<')
		return (1);
	return (0);
}



int	get_env_len(char *env_var_start, t_env_var **env_list)
{
	char	*iter;
	char	*env_var;
	int		env_var_len;
	char	char_holder;

	iter = env_var_start;
	while (*iter && (ft_isalpha(*iter) || ft_isdigit(*iter) || *iter == '_'))
		iter++;
	char_holder = *iter;
	*iter = '\0';
	env_var_len = iter - env_var_start + 1;
	env_var = malloc(env_var_len);
	strcpy(env_var, env_var_start);
	creat_list(env_list, env_var);
	*iter = char_holder;
	return (env_var_len);
}

char	*get_new_token(char *token_str)
{
	char		*token_iter;
	t_env_var	*env_list;
	int			count_token_len;
	char		*new_token;

	env_list = NULL;
	token_iter = token_str;
	count_token_len = 0;
	while (*token_iter)
	{
		if ((*token_iter == '$') && *(token_iter + 1))
			token_iter = &token_iter[(get_env_len(token_iter+1, &env_list)) - 1];
		else
			count_token_len++;
		token_iter++;
	}
	if (env_list == NULL)
		return (NULL);
	new_token = malloc(count_token_len + 1 + count_evn_vars_len(env_list));
	write_new_token(new_token, token_str, env_list);
	//TODO free the t_env that i did create
	return (new_token);
}*/

int get_env_len(char *env_var_start, t_env_var **env_list)
{
    if (!env_var_start || !*env_var_start)
        return 0;

    char *iter = env_var_start;
    int len = 0;

    // Count length of environment variable name
    while (iter[len] && (ft_isalpha(iter[len]) || ft_isdigit(iter[len]) || iter[len] == '_'))
        len++;

    if (len == 0)
        return 0;

    // Allocate and copy the environment variable name
    char *env_var = malloc(len + 1);  // +1 for null terminator
    if (!env_var)
        return 0;

    strncpy(env_var, env_var_start, len);  // Use strncpy instead of strcpy
    env_var[len] = '\0';  // Ensure null termination

    creat_list(env_list, env_var);
    return len;
}

char *get_new_token(char *token_str)
{
    if (!token_str)
        return NULL;

    t_env_var *env_list = NULL;
    char *token_iter = token_str;
    int count_token_len = 0;

    // First pass: calculate length and create env list
    while (*token_iter)
    {
        if (*token_iter == '$' && *(token_iter + 1))
        {
            int env_len = get_env_len(token_iter + 1, &env_list);
            if (env_len > 0)
                token_iter += env_len + 1;  // +1 for the '$'
            else
            {
                count_token_len++;
                token_iter++;
            }
        }
        else
        {
            count_token_len++;
            token_iter++;
        }
    }

    if (!env_list)
        return NULL;

    // Allocate new token with exact size needed
    int env_vars_len = count_evn_vars_len(env_list);
    char *new_token = malloc(count_token_len + env_vars_len + 1);  // +1 for null terminator
    if (!new_token)
    {
        // Free env_list before returning
        // Add cleanup code here
        return NULL;
    }

    // Write the new token
    write_new_token(new_token, token_str, env_list);

    // Cleanup env_list
    while (env_list)
    {
        t_env_var *temp = env_list;
        env_list = env_list->next;
        free(temp->var);
        free(temp->real_value);
        free(temp);
    }

    return new_token;
}

void write_new_token(char *new_token, char *token_str, t_env_var *env_list)
{
    char *write_ptr = new_token;

    while (*token_str)
    {
        if (*token_str == '$' && env_list)
        {
            strcpy(write_ptr, env_list->real_value);
            write_ptr += strlen(env_list->real_value);
            token_str++;  // Skip the '$'

            // Skip the environment variable name
            while (*token_str && (ft_isalpha(*token_str) || ft_isdigit(*token_str) || *token_str == '_'))
                token_str++;

            env_list = env_list->next;
        }
        else
        {
            *write_ptr++ = *token_str++;
        }
    }
    *write_ptr = '\0';
}

void	expand_varibles(t_tokens **token)
{
	t_tokens	*token_iter;
	char		*token_holder;

	token_iter = *token;
	while (token_iter)
	{
		if (!token_iter->sing_qoute)
		{
			token_holder = get_new_token(token_iter->token);
			if (token_holder != NULL)
			{
				free(token_iter->token);
				token_iter->token = token_holder;
			}
		}
		token_iter = token_iter->next;
	}
}
