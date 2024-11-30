/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:12:36 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:12:37 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_var(char *name, char *value, t_env_list *list)
{
	t_env_list	*new_node;
	t_env_list	*current;
	char		*str;
	char		*tmp;

	tmp = ft_strjoin(name, "=");
	str = ft_strjoin(tmp, value);
	current = list;
	new_node = ft_create_node(str, 0);
	ft_last_node(current)->next = new_node;
}

void	update_env(char *name, char *value)
{
	t_env_list	*var;
	char		*tmp1;

	tmp1 = ft_strdup(value);
	free(value);
	value = NULL;
	var = check_if_exit(ft_bash()->list, ft_strdup(name), 0);
	if (name[0] == 'O' && var == NULL)
		add_var(ft_strdup(name), value, ft_bash()->list);
	else if (var)
	{
		if (tmp1)
			var->value = tmp1;
	}
}

int	ft_cd_helper(char *path)
{
	int		code;
	char	*oldpwd;
	char	*pwd;

	if (path[0] == '\0')
		return (0);
	oldpwd = getcwd(NULL, 0);
	code = chdir(path);
	if (code != 0)
	{
		free(oldpwd);
		return (err_msg("No such file or directory", "cd", path), 1);
	}
	pwd = getcwd(NULL, 0);
	update_env("PWD", pwd);
	update_env("OLDPWD", oldpwd);
	return (0);
}

int	ft_cd(char **arg)
{
	int			j;
	t_env_list	*env_home;
	char		*home;

	j = 1;
	if (arg[j] == NULL)
	{
		home = ft_strdup("HOME");
		env_home = check_if_exit(ft_bash()->list, home, 0);
		if (env_home != NULL)
			return (ft_cd_helper(env_home->value));
		return (err_msg("HOME not set", "cd", NULL), 1);
	}
	while (arg[j])
		j++;
	if (j > 2)
		return (err_msg("too many arguments", "cd", NULL), 1);
	return (ft_cd_helper(arg[1]));
}
