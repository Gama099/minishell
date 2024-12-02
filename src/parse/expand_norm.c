/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hadd <sel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:14:49 by sel-hadd          #+#    #+#             */
/*   Updated: 2024/11/30 00:22:09 by sel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	creat_list(t_env_list **list, char *token)
{
	t_env_list	*env_var;
	char		*tmp_env;
	t_env_list	*tmp;

	env_var = (t_env_list *)my_malloc(sizeof(t_env_list));
	if (!env_var)
		return ;
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
		tmp = *list;
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

void	handle_dlr(char **w_ptr, char **str, t_env_list **ev_list)
{
	ft_strcpy(*w_ptr, (*ev_list)->value);
	*w_ptr += ft_strlen((*ev_list)->value);
	*str += 2;
	*ev_list = (*ev_list)->next;
}

void	write_n_t(char *new_token, char *token_str, t_env_list *env_list)
{
	char	*write_ptr;

	write_ptr = new_token;
	while (*token_str)
	{
		if (*token_str == '$' && *(token_str + 1) == '?')
			handle_dlr(&write_ptr, &token_str, &env_list);
		else if (*token_str == '$' && env_list)
		{
			ft_strcpy(write_ptr, env_list->value);
			write_ptr += ft_strlen(env_list->value);
			token_str++;
			while (1)
			{
				if (!*token_str || is_white_space(*token_str)
					|| *token_str == '$' || is_meta(*token_str))
					break ;
				token_str++;
			}
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
		return (0);
	iter = env_var_start;
	len = 0;
	while (iter[len] && (ft_isalpha(iter[len]) || ft_isdigit(iter[len])
			|| iter[len] == '_'))
		len++;
	if (len == 0)
		return (0);
	env_var = (char *)my_malloc(len + 1);
	if (!env_var)
		return (0);
	ft_strncpy(env_var, env_var_start, len);
	env_var[len] = '\0';
	creat_list(env_list, env_var);
	return (len);
}
