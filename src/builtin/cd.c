#include "minishell.h"

void	update_env(char *name, char *value)//tempo
{
	char	*tmp;
	t_env_list	*var;

	var = check_if_exit(ft_bash()->list, name);
	if (var)
	{
		if (value)
		{
			tmp = var->value;
			var->value = value;
			free(tmp);
		}
	}
	// else
	// {
	// 	tmp = ft_strdup(name);
	// 	if (tmp == NULL)
	// 		err_n_die("syscall failed", "malloc", NULL, 1);
	// 	var = ft_envnew(tmp, value, 1);
	// 	ft_envadd_back(&shell()->env, var);
	// }
}

int	ft_cd_helper(char *path)
{
	int		code;
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	code = chdir(path);
	if (code != 0)
		return (free(oldpwd), printf("No such file or directory\n"), (1));
	pwd = getcwd(NULL, 0);
	update_env("PWD", pwd);
	update_env("OLDPWD", oldpwd);
	return (0);
}

int		ft_cd(char **arg)
{
	int j;
	t_env_list	*homes;

	j = 1;
	
	if (arg[j] == NULL)//cd home if one arg
	{
		homes = check_if_exit(ft_bash()->list, "HOME");
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