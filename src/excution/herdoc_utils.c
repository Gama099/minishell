/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:14:00 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:14:01 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}

int	last_ch(char c)
{
	if (is_white_space(c))
		return (1);
	else if (is_meta(c))
		return (1);
	else if (is_qoute(c))
		return (1);
	else if (c == '$')
		return (1);
	return (0);
}

void	write_n_t_herdoc(char *new_token, char *token_str, t_env_list *env_list)
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
				if (!*token_str || last_ch(*token_str) == 1)
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

char	*get_new_token_herodc(char *token_str)
{
	t_env_list	*env_list;
	char		*token_iter;
	int			count_token_len;
	int			env_vars_len;
	char		*new_token;

	env_list = NULL;
	token_iter = token_str;
	count_token_len = 0;
	while (*token_iter)
		get_n_t_a(&token_iter, &env_list, &count_token_len);
	if (!env_list)
		return (NULL);
	env_vars_len = count_evn_vars_len(env_list);
	new_token = (char *)my_malloc(count_token_len + env_vars_len + 1);
	write_n_t_herdoc(new_token, token_str, env_list);
	return (new_token);
}

char	*expand_herdoc(char *str)
{
	char	*tmp;

	tmp = get_new_token_herodc(str);
	return (tmp);
}
