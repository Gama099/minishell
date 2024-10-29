#include "minishell.h"

void	swap_data(t_env_list *current, t_env_list *next)
{
	int		temp;
	char	*temp2;

	temp = current->type;
	current->type = next->type;
	next->type = temp;
	temp2 = current->name;
	current->name = next->name;
	next->name = temp2;
	temp2 = current->value;
	current->value = next->value;
	next->value = temp2;
}

t_env_list	*sorted_env(t_env_list *list)
{
	t_env_list	*i;
	t_env_list	*j;

	i = list;
	while (i != NULL)
	{
		j = i->next;
		while (j != NULL)
		{
			if (ft_strncmp(i->name, j->name, INT_MAX) > 0)
				swap_data(i, j);
			j = j->next;
		}
		i = i->next;
	}
	return (list);
}

t_env_list	*copyList(t_env_list *head)
{
	t_env_list	*node;

    if (head == NULL)
        return NULL;
    else
	{
        node = malloc(sizeof(t_env_list));
		if (node == NULL)
			err_n_exit("syscall failed", "malloc", NULL, 1);
        node->name = head->name;
		node->value = head->value;
        node->next = copyList(head->next);
        return node;
    }
}

void	print_export(t_env_list *list)
{
	t_env_list	*first;

	first = copyList(list);
	first = sorted_env(first);
	while(first != NULL)
	{
		if (first->name[0] != '_')
		{
			printf("declare -x ");
			if (first->value == NULL)
				printf("%s\n",first->name);
			else
				printf("%s=\"%s\"\n",first->name, first->value);
		}
		first = first->next;
	}
	free_env(first);
}
