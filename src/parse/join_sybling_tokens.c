/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_sybling_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hadd <sel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:27:44 by sel-hadd          #+#    #+#             */
/*   Updated: 2024/11/29 22:27:47 by sel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tokens	*create_node_join(t_tokens *token_a, t_tokens *token_b)
{
	t_tokens	*new_node;

	if (!token_a || !token_b)
		return (NULL);
	new_node = (t_tokens *)my_malloc(sizeof(t_tokens));
	new_node->token = ft_strjoin(token_a->token, token_b->token);
	new_node->tokentype = NULL;
	new_node->qoute_type = 0;
	new_node->join_with_next = token_b->join_with_next;
	new_node->expand_env = token_b->expand_env;
	new_node->next = token_b->next;
	return (new_node);
}

int	free_token(t_tokens **token, t_tokens **iter, t_tokens **prev)
{
	*iter = (*iter)->next;
	if (*prev)
		(*prev)->next = *iter;
	else
		*token = *iter;
	if (*token == NULL)
		return (1);
	return (0);
}

void	handle_j_with_n(t_tokens **token, t_tokens **iter, t_tokens **prev)
{
	t_tokens	*merged_nodes;

	merged_nodes = create_node_join(*iter, (*iter)->next);
	if (!merged_nodes)
		return ;
	*iter = (*iter)->next;
	if (*prev)
		(*prev)->next = merged_nodes;
	else
		*token = merged_nodes;
	*iter = merged_nodes;
}

void	join_token_syblings(t_tokens **token)
{
	t_tokens	*iter;
	t_tokens	*prev;

	iter = *token;
	prev = NULL;
	while (iter)
	{
		if (!is_spaces(iter->token) && iter->qoute_type != 2)
		{
			if (free_token(token, &iter, &prev))
				break ;
		}
		else if ((!ft_strcmps(iter->token, "$") && iter->join_with_next))
		{
			if (!free_token(token, &iter, &prev))
				break ;
		}
		else if (iter->join_with_next)
			handle_j_with_n(token, &iter, &prev);
		else
		{
			prev = iter;
			iter = iter->next;
		}
	}
}
