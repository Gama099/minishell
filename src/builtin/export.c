/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:13:02 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:13:03 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_new_var(char *str, t_env_list *list)
{
	t_env_list	*new_node;
	t_env_list	*current;

	current = list;
	new_node = ft_create_node(str, 1);
	if (new_node == NULL)
		return ;
	if (check_value(str) == 2)
		new_node->value = ft_strdup("");
	ft_last_node(current)->next = new_node;
}

void	join_var(char *str, t_env_list *node)
{
	char	**splited;

	splited = ft_split(str, '=');
	if (node->value == NULL)
	{
		node->type = 1;
		node->value = ft_strdup(splited[1]);
	}
	else
		node->value = ft_strjoin(node->value, splited[1]);
}

void	change_var(char	*str, t_env_list *node)
{
	char	**splited;

	splited = ft_split(str, '=');
	if (check_value(str) == 2)
		node->value = ft_strdup("");
	if (check_value(str) == 0)
	{
		node->type = 1;
		node->value = ft_strdup(splited[1]);
	}
}

void	check_var(t_env_list *list, int i, char *str)
{
	t_env_list	*node;

	node = check_if_exit(list, str, 1);
	if (node != NULL)
	{
		if (i == 5)
		{
			if (node->value == NULL && check_value(str) != 1)
				node->value = ft_strdup("");
			return ;
		}
		else if (i == 4)
			join_var(str, node);
		else if (i == 3)
			change_var(str, node);
	}
	else
		add_new_var(str, list);
}

int	ft_export(char **str)
{
	int	j;
	int	i;
	int	status;

	j = 1;
	status = 0;
	if (str[j] == NULL)
	{
		print_export(ft_bash()->list);
		return (0);
	}
	while (str[j])
	{
		i = arg_valid(str[j]);
		if (i != 1)
			check_var(ft_bash()->list, i, str[j]);
		else
		{
			err_msg("not a valid identifier", "export", str[j]);
			status = 1;
		}
		j++;
	}
	return (status);
}
