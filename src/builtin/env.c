/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:12:46 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:12:47 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_arg(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

void	ft_env_i(void)
{
	char	**env;

	env = (char **)my_malloc((4) * sizeof(char *));
	env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	ft_bash()->list = env_to_list(env);
}

int	ft_env(t_env_list *list, char **str)
{
	t_env_list	*new_node;
	int			i;

	new_node = list;
	i = ft_check_arg(str);
	if (i > 1)
		return (err_msg("Too Many arguments", "env", NULL), 1);
	while (new_node != NULL)
	{
		if (new_node->type == 1)
		{
			write(1, new_node->name, ft_strlen(new_node->name));
			if (!ft_strcmp(new_node->name, "_"))
				write(1, "=/usr/bin/env\n", 14);
			else
				printf("=%s\n", new_node->value);
		}
		new_node = new_node->next;
	}
	return (0);
}
