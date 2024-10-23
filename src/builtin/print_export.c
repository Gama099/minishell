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

// t_env_list *duplicat_env(t_env_list *env)
// {
// 	t_env_list	*head;
// 	t_env_list	*prev;
// 	t_env_list	*tmp;

// 	tmp = env;
// 	head = NULL;
// 	prev = NULL;

// 	while (tmp != NULL)
// 	{
// 		if (head == NULL)
// 		{

// 		}
// 	}
// }

void	print_export(t_env_list *list)
{
	t_env_list *first;

	first = sorted_env(list);
	while(first != NULL)
	{
		printf("declare -x ");
		if (first->value == NULL)
			printf("%s\n",first->name);
		else
			printf("%s=\"%s\"\n",first->name, first->value);
		first = first->next;
	}
}