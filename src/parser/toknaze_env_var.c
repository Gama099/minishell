#include "../../includes/minishell.h"

static void typing_nodes(t_tokens *iter, t_tokens **list)
{
    t_tokens *current;

	current = *list;
    while (current && current->next)
	{
        current->tokenType = iter->tokenType;  // Copy the type
        current = current->next;              // Move to the next node
    }
    if (current)
	{
        current->tokenType = iter->tokenType;  // Copy the type for the last node
        current->next = iter->next;           // Connect the last node to the remaining list
    }
}


void tokenaze_var(t_tokens **tokens)
{
    t_tokens *iter = *tokens;
    t_tokens *prev = NULL;
	t_tokens *tmp_holder = NULL;
	t_tokens *to_free;

    while (iter)
	{
        if (iter->expand_env && iter->qoute_type != 2)
		{
            tmp_holder = getTokens(ft_strdup(iter->token));

            if (!tmp_holder) {
                printf("Error: Variable expansion failed.\n");
                return;
            }

            // Update the token types and connect the new tokens
            typing_nodes(iter, &tmp_holder);

            // Reconnect the list
            if (prev) {
                prev->next = tmp_holder;
            } else {
                *tokens = tmp_holder;  // Update head if the first token is expanded
            }

            // Move to the next node and free the original
            to_free = iter;
            iter = iter->next;
            free(to_free);
        }
		else
		{
            prev = iter;
            iter = iter->next;
        }
    }
}

