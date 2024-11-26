#include "../../includes/minishell.h"

int	dot_only(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != '.')
			return (1);
		i++;
	}
	err_n_exit("command not found", NULL, cmd, 127);
	return (0);
}

char	*get_path(void)
{
	char		**env;
	char		*path;
	char		*tmp;
	t_env_list	*node;
	int			i;

	i = 0;
	env = env_to_ary(ft_bash()->list);
	while (env[i])
	{
		tmp = ft_strnstr(env[i], "PATH", 4);
		path = ft_strdup(tmp);
		if (path != NULL)
		{
			free(path);
			node = check_if_exit(ft_bash()->list, "PATH", 2);
			return (free_ary(env), node->value);
		}
		i++;
	}
	return (free_ary(env), NULL);
}

void	check_exit(int check, char *cmd, char *tmp, char **splited)
{
	free_ary(splited);
	free(tmp);
	tmp = NULL;
	if (check == 1)
		err_n_exit("command not found", NULL, cmd, 127);
	else if (check == 2)
		err_n_exit("permission denied", NULL, cmd, 126);
}

char	*find_path(char *cmd)
{
	char	*path;
	char	**splited_path;
	char	*tmp;
	int		i;
	int		check;

	i = 0;
	dot_only(cmd);
	splited_path = split_env();
	tmp = ft_strjoin("/", cmd);
	while (splited_path[i])
	{
		path = ft_strjoin(splited_path[i], tmp);
		check = check_access(path);
		if (check == 0)
			return (free(tmp), free_ary(splited_path), path);
		else
			free(path);
		i++;
	}
	check_exit(check, cmd, tmp, splited_path);
	return (NULL);
}
