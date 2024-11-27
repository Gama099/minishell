#include "../../includes/minishell.h"

void	typing_nodes(t_tokens *iter, t_tokens **list)
{
	t_tokens	*current;

	current = *list;
	while (current && current->next)
	{
		current->tokenType = iter->tokenType;
		current = current->next;
	}
	if (current)
	{
		current->tokenType = iter->tokenType;
		current->next = iter->next;
	}
}

void	tokenaze_var_a(t_tokens **tokens, t_tokens **prev, t_tokens **iter)
{
	t_tokens	*tmp_holder;
	t_tokens	*to_free;

	tmp_holder = get_tokens(ft_strdup((*iter)->token));
	if (!tmp_holder)
		return ;
	typing_nodes((*iter), &tmp_holder);
	if (*prev)
		(*prev)->next = tmp_holder;
	else
		*tokens = tmp_holder;
	to_free = *iter;
	*iter = (*iter)->next;
	free(to_free);
}

void	tokenaze_var(t_tokens **tokens)
{
	t_tokens	*iter;
	t_tokens	*prev;

	prev = NULL;
	iter = *tokens;
	iter = *tokens;
	prev = NULL;
	while (iter)
	{
		if (iter->expand_env && iter->qoute_type != 2)
			tokenaze_var_a(tokens, &prev, &iter);
		else
		{
			prev = iter;
			iter = iter->next;
		}
	}
}
