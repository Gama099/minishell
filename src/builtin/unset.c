#include "../../includes/minishell.h"

// void	node_del(t_env_list *node)
// {
// 	if (node)
// 	{
// 		free(node->name);
// 		node->name = NULL;
// 		free(node->value);
// 		node->value = NULL;
// 	}
// 	free(node);
// 	node = NULL;
// }

void	ft_unset_helper(t_env_list *node, t_env_list *prev, t_env_list **list)
{
	if (node != NULL)
	{
		if (prev == NULL)
			*list = node->next;
		else
		{
			if (node->next != NULL)
				prev->next = node->next;
			else
				prev->next = NULL;
		}
	}
}

int	ft_unset(char **argv, t_env_list **list)
{
	t_env_list	*new_node;
	t_env_list	*prev;
	int			j;

	j = 1;
	while (argv[j])
	{
		new_node = *list;
		prev = NULL;
		while (new_node && (ft_strncmp(argv[j], new_node->name, INT_MAX)))
		{
			prev = new_node;
			new_node = new_node->next;
		}
		ft_unset_helper(new_node, prev, list);
		j++;
	}
	return (0);
}
