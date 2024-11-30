/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenaze.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hadd <sel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:38:48 by sel-hadd          #+#    #+#             */
/*   Updated: 2024/11/30 01:12:39 by sel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_tokens(t_tokens **token, char *str, int qoute, int to_join)
{
	t_tokens	*new_node;
	t_tokens	*last;

	new_node = (t_tokens *)my_malloc(sizeof(t_tokens));
	new_node->token = ft_strdup(str);
	if (!new_node->token)
		return ;
	new_node->next = NULL;
	new_node->qoute_type = qoute;
	new_node->join_with_next = to_join;
	new_node->tokentype = NULL;
	new_node->expand_env = 0;
	if (!*token)
		*token = new_node;
	else
	{
		last = *token;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
	return ;
}

void	init_params(t_params *params, char *buffer)
{
	params->iter = buffer;
	params->token_begin = buffer;
	params->in_qoutes = 0;
	params->which_qoute = '\0';
	params->tokens = NULL;
	params->to_join = 0;
}
