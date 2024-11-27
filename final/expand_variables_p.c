#include "expand.h"


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
    t_env_list	*env_var;
    char		*tmp_env;

    env_var = malloc(sizeof(t_env_list));
    if (!env_var)
        return;
    env_var->name = ft_strdup(token);
    tmp_env = ft_getenv(token);
    if (tmp_env == NULL)
        env_var->value = ft_strdup(" ");
    else
        env_var->value = ft_strdup(tmp_env);
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
void	write_new_token(char *new_token, char *token_str, t_env_list *env_list)
{
    char *write_ptr;

	write_ptr = new_token;
    while (*token_str)
	{
        if (*token_str == '$' && env_list)
		{
            strcpy(write_ptr, env_list->value);
            write_ptr += strlen(env_list->value);
            token_str++;
			while ((*token_str) && (is_white_space(*token_str)
				|| *token_str != '$'))
                token_str++;
            env_list = env_list->next;
        }
		else
			*write_ptr++ = *token_str++;
    }
    *write_ptr = '\0';
}

int	get_env_len(char *env_var_start, t_env_list **env_list)
{
    char	*iter;
	char	*env_var;
	int		len;

    if (!env_var_start || !*env_var_start)
        return 0;
	iter = env_var_start;
    len = 0;
    while (iter[len] && (isalpha(iter[len]) || isdigit(iter[len]) || iter[len] == '_'))
		len++;
    if (len == 0)
        return 0;
    env_var = malloc(len + 1);
    if (!env_var)
        return 0;
    strncpy(env_var, env_var_start, len);
    env_var[len] = '\0';
    creat_list(env_list, env_var);
    return len;
}
