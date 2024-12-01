/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:14:14 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:14:15 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_list	*ft_create_node(char *str, int mode)
{
	t_env_list	*new_node;
	int			flag;

	new_node = (t_env_list *)my_malloc(sizeof(t_env_list));
	fill_node(new_node, str, mode);
	flag = check_value(str);
	if (flag == 0 || flag == 2)
		new_node->type = 1;
	else
		new_node->type = 0;
	new_node->next = NULL;
	return (new_node);
}

void	update_sh(t_env_list *list)
{
	t_env_list	*node;

	node = check_if_exit(list, "SHLVL", 2);
	if (node != NULL)
		node->value = ft_itoa(ft_atoi(node->value) + 1);
}

t_env_list	*env_to_list(char	**env)
{
	int			i;
	t_env_list	*current;
	t_env_list	*new_node;
	t_env_list	*first;

	i = 0;
	current = NULL;
	while (env[i])
	{
		new_node = ft_create_node(env[i], 0);
		if (current == NULL)
		{
			current = new_node;
			first = current;
		}
		else
			ft_last_node(current)->next = new_node;
		i++;
	}
	update_sh(first);
	return (first);
}

void	free_env(t_env_list *env)
{
	t_env_list	*tmp;

	while (env != NULL)
	{
		tmp = env;
		env = env->next;
		free(tmp);
		tmp = NULL;
	}
	env = NULL;
}
