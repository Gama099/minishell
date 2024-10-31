#include "../../includes/minishell.h"


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

void	write_new_token(char *new_token, char *token_str, t_env_var *env_list)
{
	while (*token_str)
	{
		if (*token_str == '$')
		{
			strcpy(new_token, env_list->real_value);
			new_token = &new_token[ft_strlen(env_list->real_value)];
			token_str++;
			while ((ft_isalpha(*token_str)) || ft_isdigit(*token_str) || *token_str == '_')
				token_str++;
			env_list = env_list->next;
		}
		else
			*new_token++ = *token_str++;
	}
	*new_token = '\0';
}

int	is_meta_char(char character)
{
	if (character == '$' || character == '>' || character == '<')
		return (1);
	return (0);
}

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
