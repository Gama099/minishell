#include "minishell.h"

void	node_del(t_env_list *node)
{
	if (node)
	{
		free(node->name);
		free(node->value);
	}
	free(node);
	node = NULL;
}

int	ft_unset(char **argv, t_env_list **list)
{
	t_env_list *new_node;
	t_env_list	*prev;
	int	j;

	j = 1;
	while (argv[j])
	{
		new_node = *list;
		prev = NULL;
		while (new_node && (ft_strncmpp(argv[j], new_node->name, INT_MAX)))
		{
			prev = new_node;
			new_node = new_node->next;
		}
		if (new_node != NULL)
		{
			if (prev == NULL)// first node
				*list = new_node->next;
			else
			{
				if (new_node->next != NULL)//
					prev->next = new_node->next;
				else
					prev->next = NULL;
			}
			node_del(new_node);
		}
		j++;
	}
	return(0);
}
