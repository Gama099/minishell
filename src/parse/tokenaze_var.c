#include "../../includes/minishell.h"


void typing_nodes(t_tokens *iter, t_tokens **list)
{
    t_tokens *current;

    current = *list;
    while (current && current->next)
    {
        current->tokenType = iter->tokenType;
        current = current->next;
    }
    if (current)
    {
        current->tokenType = iter->tokenType;
    }
}



t_tokens	*last_token(t_tokens *tokens)
{
	while (tokens->next)
		tokens = tokens->next;
	return (tokens);
}

void tokenaze_var(t_tokens **tokens)
{
	t_tokens	*iter;
	t_tokens	*tmp_holder;
	t_tokens	*last;
	t_tokens	*prev;
	t_tokens	*to_free;

	iter = *tokens;
	prev = NULL;
	while (iter)
	{
		if (!iter)
			return ;
		if (iter->expand_env && iter->qoute_type == 0)
		{
			tmp_holder = get_tokens(iter->token, 1);
			typing_nodes(iter, &tmp_holder);
			last = last_token(tmp_holder);
			to_free = iter;
			iter = iter->next;
			if (prev)
			{
				prev->next = tmp_holder;
				last->next = iter;
				prev = last;
			}
			else
			{
				*tokens = tmp_holder;
				last->next = iter;
				prev = last;
			}
		}
		else{
			prev = iter;
			iter = iter->next;
		}
	}
}
