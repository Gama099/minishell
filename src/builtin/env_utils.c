/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:12:51 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:12:52 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_counter(t_env_list *env)
{
	int	i;

	i = 0;
	while (env->next != NULL)
	{
		env = env->next;
		i++;
	}
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	i = 0;
	while (s1 && s2 && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

t_env_list	*check_if_exit(t_env_list *list, char *str, int mode)
{
	t_env_list	*node;
	char		**splited;

	node = list;
	if (mode == 1)
	{
		if (there_is_plus(str) == 0)
			splited = ft_split(str, '+');
		else
			splited = ft_split(str, '=');
		while (node != NULL)
		{
			if ((ft_strcmp(node->name, splited[0])) == 0)
				return (node);
			node = node->next;
		}
		return (NULL);
	}
	while (node != NULL)
	{
		if ((ft_strcmp(node->name, str)) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

char	**env_to_ary(t_env_list *envp)
{
	char	**env_ar;
	int		i;
	int		j;
	char	*tmp;

	i = env_counter(envp);
	j = 0;
	env_ar = (char **)my_malloc(sizeof(char *) * (i + 2));
	while (j <= i)
	{
		tmp = ft_strjoin(envp->name, "=");
		env_ar[j] = ft_strjoin(tmp, envp->value);
		j++;
		envp = envp->next;
	}
	env_ar[j] = NULL;
	return (env_ar);
}
