#include "../../includes/minishell.h"

int	set_under_score(char **argv) //to be fixed
{
	t_env_list	*node;
	char		*value;
	int			i;

	i = 0;
	while (argv[i])
		i++;
	if (i == 0)
		return (1);
	node = check_if_exit(ft_bash()->list, "_", 0);
	value = node->value;
	node->value = ft_strdup(argv[i - 1]);
	free(value);
	return (0);
}

int	check_access(char *PATH)
{
	if (access(PATH, F_OK) == 0)
	{
		if (access(PATH, X_OK) == 0)
			return (0);
		else
			return (2);
	}
	else
		return (1);
}

char	*get_path(void)
{
	char	**env;
	char	*path;
	int		i;

	i = 0;
	env = env_to_ary(ft_bash()->list);
	while (env[i])
	{
		path = ft_strnstr(env[i], "PATH", 4);
		if (path != NULL)
			return (path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd)
{
	char	*path;
	char	**splited_path;
	char	*tmp;
	int		i;
	int		check;

	i = 0;
	check = 0;
	path = get_path();
	splited_path = ft_split(path, ':');
	tmp = ft_strjoin("/", cmd);
	while (splited_path[i])
	{
		path = ft_strjoin(splited_path[i], tmp);
		check = check_access(path);
		if (check == 0)
			return (free(tmp), free(splited_path), path);
		i++;
	}
	if (check == 1)
		err_n_exit("command not found", NULL, cmd, 127);
	else if (check == 2)
		err_n_exit("permission denied", NULL, cmd, 126);
	return (NULL);
}

char	**env_to_ary(t_env_list *envp)
{
	char	**env_ar;
	int		i;
	int		j;

	i = count_pipe(envp, 2);
	j = 0;
	env_ar = (char **)malloc(sizeof(char *) * (i + 2));
	if (env_ar == NULL)
		err_n_exit("syscall failed", "malloc", NULL, 1);
	while (j <= i)
	{
		env_ar[j] = ft_strjoin(ft_strjoin(envp->name, "="), envp->value);
		j++;
		envp = envp->next;
	}
	env_ar[j] = NULL;
	return (env_ar);
}
