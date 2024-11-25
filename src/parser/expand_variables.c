#include "../../includes/minishell.h"

char	*ft_getenv(char *token)
{
	t_env_list	*iter;

	iter = ft_bash()->list;
	while (iter)
	{
		if (!ft_strcmps(iter->name, token))
			return(iter->value);
		iter = iter->next;
	}
	return (NULL);
}

void creat_list(t_env_list **list, char *token)
{
    t_env_list *env_var;
    char *tmp_env;

    env_var = malloc(sizeof(t_env_list));
    if (!env_var)
        return;
    env_var->name = ft_strdup(token); // Ensure you duplicate the token
    tmp_env = ft_getenv(token);
	free(token);
    if (tmp_env == NULL)
        env_var->value = ft_strdup(" "); // Consider using an empty string instead
	else
		env_var->value = ft_strdup(tmp_env);
    env_var->next = NULL;
    if (!*list)
        *list = env_var;
    else
	{
        t_env_list *tmp = *list;
        while (tmp->next) {
            tmp = tmp->next;
        }
        tmp->next = env_var;
    }
}

int	count_evn_vars_len(t_env_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		count += ft_strlen(list->value);
		list = list->next;
	}
	return (count);
}

void	write_new_token(char *new_token, char *token_str, t_env_list *env_list);

int	get_env_len(char *env_var_start, t_env_list **env_list)
{
	char	*env_var;

    if (!env_var_start || !*env_var_start)
        return 0;
    char *iter = env_var_start;
    int len = 0;
    while (iter[len] && (ft_isalpha(iter[len]) || !ft_isdigit(iter[len]) || iter[len] == '_'))
		len++;
    if (len == 0)
        return 0;
    env_var = malloc(len + 1);  // +1 for null terminator
    if (!env_var)
        return 0;
    strncpy(env_var, env_var_start, len);  // Use strncpy instead of strcpy
    env_var[len] = '\0';  // Ensure null termination
    creat_list(env_list, env_var);
    return len;
}

void creat_list_state(t_env_list **list)
{
    t_env_list *env_var;

    env_var = malloc(sizeof(t_env_list));
    if (!env_var)
        return;
    env_var->name = ft_strdup("?");  // Ensure you duplicate the token
	env_var->value = ft_strdup(ft_itoa(ft_bash()->exit_status));
    env_var->next = NULL;
    if (!*list)
        *list = env_var;
	else
	{
        t_env_list *tmp = *list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = env_var;
    }
}

char *get_new_token(char *token_str)
{
	if (!token_str)
        return NULL;
	t_env_list *env_list = NULL;
    char *token_iter = token_str;
    int count_token_len = 0;
    while (*token_iter)
    {
		if (*token_iter == '$' && *(token_iter + 1) == '?')
		{
			creat_list_state(&env_list);
			count_token_len += ft_strlen(ft_itoa(ft_bash()->exit_status));
			token_iter += 2;
		}
        else if (*token_iter == '$' && *(token_iter + 1))
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
    int env_vars_len = count_evn_vars_len(env_list);
    char *new_token = malloc(count_token_len + env_vars_len + 1);  // +1 for null terminator
    if (!new_token)
        return (free_env(env_list), NULL);
    write_new_token(new_token, token_str, env_list);
    return (free_env(env_list), new_token);
}

void write_new_token(char *new_token, char *token_str, t_env_list *env_list)
{
    char *write_ptr = new_token;

    while (*token_str) {
        if (*token_str == '$' && env_list) {
            strcpy(write_ptr, env_list->value);
            write_ptr += ft_strlen(env_list->value);
            token_str++;  // Skip the '$'
			while ((*token_str) && (is_white_space(*token_str) || *token_str != '$'))
                 token_str++;
            // Skip the environment variable name
            // while (*token_str && ((isalpha(*token_str) || isdigit(*token_str) || *token_str == '_'|| *token_str == '?')) )
            //     token_str++;
            env_list = env_list->next; // Move to the next environment variable
        }
		else
            *write_ptr++ = *token_str++;
    }
    *write_ptr = '\0';  // Null-terminate the new token
}

void	expand_varibles(t_tokens **token)
{
	t_tokens	*token_iter;
	char		*token_holder;
	int			is_herdoc;

	token_iter = *token;
	is_herdoc = 0;
	while (token_iter)
	{
		if (!ft_strcmps(token_iter->token, "<<") ||
            !ft_strcmps(token_iter->token, "<") ||
            !ft_strcmps(token_iter->token, ">") ||
            !ft_strcmps(token_iter->token, ">>"))
		{
			is_herdoc = 1;
			if (token_iter->next)
				token_iter = token_iter->next;
			else
				break;
		}
		else if ((token_iter->qoute_type == 0 || token_iter->qoute_type == 2) && !is_herdoc)
		{
			token_holder = get_new_token(token_iter->token);
			if (token_holder != NULL)
			{
				token_iter->expand_env = 1;
				free(token_iter->token);
				token_iter->token = token_holder;
			}
		}
		is_herdoc = 0;
		token_iter = token_iter->next;
	}
	clean_list_spaces(token);
}

void    clean_list_spaces(t_tokens **token)
{
    t_tokens    *current;
    t_tokens    *prev;
    t_tokens    *to_free;

    current = *token;
    prev = NULL;
    while (current)
    {
        if (!is_spaces(current->token) && current->qoute_type != 2)
        {
            to_free = current;
            current = current->next;
            if (prev)
                prev->next = current;
            else
                *token = current->next;
            free(to_free);
        }
        else
		{
            prev = current;
            current = current->next;
		}
    }
}
