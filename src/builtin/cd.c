#include "../../includes/minishell.h"

void	add_var(char *name, char *value, t_env_list *list)
{
	t_env_list	*new_node;
	t_env_list	*current;
	char		*str;
	char		*tmp;

	tmp = ft_strjoin(name, "=");
	str = ft_strjoin(tmp, value);
	free(tmp);
	current = list;
	new_node = ft_create_node(str);
	if (new_node == NULL)
		return ;
	ft_last_node(current)->next = new_node; //add new var to env linked list
}

void	update_env(char *name, char *value)//tempo
{
	char		*tmp;
	t_env_list	*var;

	var = check_if_exit(ft_bash()->list, name, 0);
	if (name[0] == 'O' && var == NULL)
		add_var(name, value, ft_bash()->list);
	else if (var)
	{
		if (value)
		{
			tmp = var->value;
			var->value = value;
			free(tmp);
		}
		free(name);
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
	update_env(ft_strdup("PWD"), pwd);
	update_env(ft_strdup("OLDPWD"), oldpwd);
	return (0);
}

int	ft_cd(char **arg)
{
	int			j;
	t_env_list	*env_home;
	char		*home;

	j = 1;
	if (arg[j] == NULL) //arg contain only cd
	{
		home = ft_strdup("HOME");
		env_home = check_if_exit(ft_bash()->list, home, 0);
		free(home);
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
