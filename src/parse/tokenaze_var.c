/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenaze_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hadd <sel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:40:04 by sel-hadd          #+#    #+#             */
/*   Updated: 2024/11/30 00:40:00 by sel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	typing_nodes(t_tokens *iter, t_tokens **list)
{
	t_tokens	*current;

	current = *list;
	while (current && current->next)
	{
		current->tokentype = iter->tokentype;
		current = current->next;
	}
	if (current)
	{
		current->tokentype = iter->tokentype;
	}
}

t_tokens	*last_token(t_tokens *tokens)
{
	while (tokens->next)
		tokens = tokens->next;
	return (tokens);
}

void	expand_env_variable(t_tokens *iter, t_tokens **tokens, t_tokens *prev)
{
	t_tokens	*tmp_holder;
	t_tokens	*last;

	tmp_holder = get_tokens(iter->token, 1);
	typing_nodes(iter, &tmp_holder);
	last = last_token(tmp_holder);
	iter = iter->next;
	if (prev)
		prev->next = tmp_holder;
	else
		*tokens = tmp_holder;
	last->next = iter;
}

void	tokenaze_var(t_tokens **tokens)
{
	t_tokens	*iter;
	t_tokens	*prev;
	int			f;

	iter = *tokens;
	prev = NULL;
	while (iter)
	{
		f = 0;
		if (prev)
		{
			if (!ft_strcmps(prev->token, "export"))
				f = 1;
		}
		if (iter->expand_env && iter->qoute_type == 0 && !f)
		{
			expand_env_variable(iter, tokens, prev);
			iter = iter->next;
		}
		else
		{
			prev = iter;
			iter = iter->next;
		}
	}
}
