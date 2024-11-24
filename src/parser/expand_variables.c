#include "../../includes/minishell.h"


static size_t	count_nbr(int nbr)
{
	size_t	count;

	count = 0;
	if (nbr < 0)
	{
		if (nbr == -2147483648)
			return (11);
		nbr *= -1;
		count++;
	}
	if (nbr < 10)
		return (++count);
	while (nbr > 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

static void	fill(char *str, int n, size_t len)
{
	if (n == 0)
		str[0] = '0';
	if (n == -2147483648)
	{
		str[0] = '-';
		str[--len] = '8';
		n = 214748364;
	}
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;

	len = count_nbr(n);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	fill(str, n, len);
	return (str);
}


/*void	creat_list(t_env_var **list, char *token)
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
}*/

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
    if (!env_var) {
        // Handle memory allocation failure
        return;
    }

    env_var->name = ft_strdup(token); // Ensure you duplicate the token
    tmp_env = ft_getenv(token);
    if (tmp_env == NULL) {
        env_var->value = ft_strdup(" "); // Consider using an empty string instead
    } else {
        env_var->value = ft_strdup(tmp_env);
    }
    env_var->next = NULL;

    if (!*list) {
        *list = env_var;
    } else {
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

//void	write_new_token(char *new_token, char *token_str, t_env_list *env_list);
void	write_new_token(char *new_token, char *token_str, t_env_list *env_list);/*
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

int	get_env_len(char *env_var_start, t_env_list **env_list)
{
    if (!env_var_start || !*env_var_start)
        return 0;
    char *iter = env_var_start;
    int len = 0;
    while (iter[len] && (isalpha(iter[len]) || isdigit(iter[len]) || iter[len] == '_'))
		len++;
    if (len == 0)
        return 0;
    char *env_var = malloc(len + 1);  // +1 for null terminator
    if (!env_var)
        return 0;
    strncpy(env_var, env_var_start, len);  // Use strncpy instead of strcpy
    env_var[len] = '\0';  // Ensure null termination
    creat_list(env_list, env_var);
    return len;
}

void creat_list_state(t_env_list **list, char *token)
{
    t_env_list *env_var;
    char *tmp_env;

    env_var = malloc(sizeof(t_env_list));
    if (!env_var) {
        // Handle memory allocation failure
        return;
    }

    env_var->name = ft_strdup("?"); // Ensure you duplicate the token
    //printf("in struct %d\n", ft_bash()->exit_status);
	env_var->value = ft_strdup(ft_itoa(ft_bash()->exit_status));
    env_var->next = NULL;

    if (!*list) {
        *list = env_var;
    } else {
        t_env_list *tmp = *list;
        while (tmp->next) {
            tmp = tmp->next;
        }
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
    // First pass: calculate length and create env list
    while (*token_iter)
    {
		if (*token_iter == '$' && *(token_iter + 1) == '?')
		{
			// add to env_list and count
			creat_list_state(&env_list, ft_itoa(ft_bash()->exit_status));
			count_token_len += strlen(ft_itoa(ft_bash()->exit_status));
			//printf("here [%s]\n", token_iter);
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
    // Allocate new token with exact size needed
    int env_vars_len = count_evn_vars_len(env_list);
	//printf("env_vars_len = %d\n", env_vars_len);
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
    /*while (env_list)
    {
        t_env_var *temp = env_list;
        env_list = env_list->next;
        free(temp->var);
        free(temp->real_value);
        free(temp);
    }*/
    return new_token;
}

void write_new_token(char *new_token, char *token_str, t_env_list *env_list)
{
    char *write_ptr = new_token;

    while (*token_str) {
		//printf("hnaya [%c]\n", *token_str);
        if (*token_str == '$' && env_list) {
            strcpy(write_ptr, env_list->value);
            write_ptr += strlen(env_list->value);
            token_str++;  // Skip the '$'

            // Skip the environment variable name
            while (*token_str && (isalpha(*token_str) || isdigit(*token_str) || *token_str == '_') || *token_str == '?') {
                token_str++;
            }
            env_list = env_list->next; // Move to the next environment variable
        } else {
            *write_ptr++ = *token_str++;
        }
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
}

/*char	*get_new_token(char *token)
{
	char		*token_iter;
	int			count_token_len;
	t_env_var	*paste_list;

	paste_list = NULL;
	token_iter = token;
	while (*token_iter)
	{
		if (*token_iter == '$' && *(token_iter + 1) == '?')
			printf("to handle retuning last state\n");
		else if (*token_iter == '$' && *(token_iter + 1))
		{
			set_var_name_paste_list(token_iter, paste_list);
			get_env_len(count_token_len, envs_list);// i have to give the var name
		}
		else
			token_iter++;
	}
}

void	set_var_name_paste_list(char *var_name, t_env_var *paste_list)
{
	char	*start;

	start = var_name;
	while (*var_name && (ft_isalpha(*var_name) || ft_isdigit(*var_name) || *var_name == '_'))
                var_name++;

}

void	get_env_len(int len, t_env_var *paste_list)
{
	t_env_list	*iter_list;

	iter_list = ft_bash()->list;
	while (iter_list->next)
	{
		if (ft_strncmp(iter_list->name, paste_list->var,
			ft_strlen(iter_list->name)))
		{

		}
	}
}
*/
