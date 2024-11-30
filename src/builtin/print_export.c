/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:13:13 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:13:15 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_env_list	*copylist(t_env_list *head)
{
	t_env_list	*node;

	if (head == NULL)
		return (NULL);
	else
	{
		node = malloc(sizeof(t_env_list));
		if (node == NULL)
			err_n_ex("syscall failed", "malloc", NULL, 1);
		node->name = ft_strdup(head->name);
		node->value = ft_strdup(head->value);
		node->type = head->type;
		node->next = copylist(head->next);
		return (node);
	}
}

void	print_export(t_env_list *list)
{
	t_env_list	*first;
	t_env_list	*current;

	first = copylist(list);
	first = sorted_env(first);
	current = first;
	while (current != NULL)
	{
		if (current->name[0] == '_' && ft_strlen(current->name) == 1)
			current = current->next;
		else
		{
			printf("declare -x ");
			if (current->value == NULL)
				printf("%s\n", current->name);
			else
				printf("%s=\"%s\"\n", current->name, current->value);
			current = current->next;
		}
	}
	free_env(first);
}
