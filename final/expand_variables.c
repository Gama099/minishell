#include "expand.h"


void creat_list_state(t_env_list **list, char *token)
{
    t_env_list	*env_var;
    char		*tmp_env;
	t_env_list	*tmp;

    env_var = malloc(sizeof(t_env_list));
    if (!env_var)
        return;

    env_var->name = ft_strdup("?");
	env_var->value = ft_strdup(ft_itoa(ft_bash()->exit_status));
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

void get_new_token_a(char **token_iter, t_env_list **env_list, int *token_len)
{
    if (**token_iter == '$' && *(*token_iter + 1) == '?')
    {
        creat_list_state(env_list, ft_itoa(ft_bash()->exit_status));
        *token_len += strlen(ft_itoa(ft_bash()->exit_status));
        *token_iter += 2;
    }
    else if (**token_iter == '$' && *(*token_iter + 1))
    {
        int env_len = get_env_len(*token_iter + 1, env_list);
        if (env_len > 0)
            *token_iter += env_len + 1;
        else
        {
            (*token_len)++;
            (*token_iter)++;
        }
    }
    else
    {
        (*token_len)++;
        (*token_iter)++;
    }
}

char *get_new_token(char *token_str)
{
	t_env_list	*env_list;
    char		*token_iter;
    int			count_token_len;
	int			env_vars_len;
	char		*new_token;

    if (!token_str)
        return NULL;
	env_list = NULL;
    token_iter = token_str;
    count_token_len = 0;
    while (*token_iter)
    {
		get_new_token_a(&token_iter, &env_list, &count_token_len);
	}
    if (!env_list)
			return NULL;
    env_vars_len = count_evn_vars_len(env_list);
    new_token = malloc(count_token_len + env_vars_len + 1);
    if (!new_token)
        return NULL;
    write_new_token(new_token, token_str, env_list);
    return new_token;
}


void	update_token(t_tokens *iter)
{
    char *token_holder;

	token_holder = get_new_token(iter->token);
    if (token_holder != NULL)
    {
        iter->expand_env = 1;
        free(iter->token);
        iter->token = token_holder;
    }
}

void	expand_varibles(t_tokens **token)
{
	t_tokens	*iter;
	char		*token_holder;
	int			is_herdoc;

	iter = *token;
	is_herdoc = 0;
	while (iter)
	{
		if (!ft_strcmps(iter->token, "<<") ||
            !ft_strcmps(iter->token, "<") ||
            !ft_strcmps(iter->token, ">") ||
            !ft_strcmps(iter->token, ">>"))
		{
			is_herdoc = 1;
			if (!iter->next)
				break;
			iter = iter->next;
		}
		else if ((iter->qoute_type == 0 || iter->qoute_type == 2)
			&& !is_herdoc)
			update_token(iter);
		is_herdoc = 0;
		iter = iter->next;
	}
}
