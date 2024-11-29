/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_token_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hadd <sel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:26:31 by sel-hadd          #+#    #+#             */
/*   Updated: 2024/11/30 00:22:21 by sel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(char *token)
{
	t_env_list	*iter;

	iter = ft_bash()->list;
	while (iter)
	{
		if (!ft_strcmps(iter->name, token))
			return (iter->value);
		iter = iter->next;
	}
	return (NULL);
}

int	is_word(char *token)
{
	while (*token)
	{
		if (!ft_isalpha(*token))
			return (0);
		token++;
	}
	return (1);
}

int	is_path(char *token)
{
	char	*iter;

	if (!token || !ft_strlen(token))
		return (0);
	iter = token;
	if (token[0] != '/' && token[0] != '.')
		return (0);
	while (*iter)
	{
		if (!(ft_isalnum(*iter) || *iter == '/' || *iter == '.' || *iter == '_'
				|| *iter == '-' || *iter == ' '))
			return (0);
		iter++;
	}
	return (1);
}

int	checkcommand(char *token)
{
	if (!is_word(token) && !is_path(token))
		return (0);
	else
		return (1);
}
