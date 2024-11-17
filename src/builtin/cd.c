#include "../../includes/minishell.h"

void	update_env(char *name, char *value)//tempo
{
	char		*tmp;
	t_env_list	*var;

	var = check_if_exit(ft_bash()->list, name, 0);
	if (var)
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
	t_env_list	*homes;
	char		*home;

	j = 1;
	if (arg[j] == NULL) //arg contain only cd
	{
		home = ft_strdup("HOME");
		homes = check_if_exit(ft_bash()->list, home, 0);
		free(home);
		if (homes != NULL)
			return (ft_cd_helper(homes->value));
		return (printf("HOME not set\n"), 1);
	}
	while (arg[j])
		j++;
	if (j > 2)
		return (printf("too many arguments\n"), 1);
	return (ft_cd_helper(arg[1]));
}
