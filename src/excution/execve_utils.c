#include "../../includes/minishell.h"

int	check_path(t_command *cmd)
{
	int	check;

	check = 0;
	if (ft_strchrr(cmd->argumants[0], '/') != -1)
	{
		if (is_a_directory(cmd->argumants[0], 1))
			clean_exit(126);
		check = check_access(cmd->argumants[0]);
		if (check == 1) // not found
			err_n_exit(NULL, NULL, cmd->argumants[0], 127);
		else if (check == 2) //not excutable
			err_n_exit(NULL, NULL, cmd->argumants[0], 126);
		else
			return (3); //path is valid
	}
	return (check);
}

int	set_under_score(char **argv) //to be fixed
{
	char		*value;
	int			i;

	i = 0;
	while (argv[i])
		i++;
	if (i == 0)
		return (1);
	value = ft_strdup(argv[i - 1]);
	update_env(ft_strdup("_"), value);
	return (0);
}

int	check_access(char *path)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
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
	char	*tmp;
	t_env_list	*node;
	int		i;

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

void	check_exit(int check, char *cmd)
{
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
	check = 0;
	tmp = get_path();
	if (tmp == NULL)
		return (free(tmp), NULL);
	splited_path = ft_split(tmp, ':');
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
	check_exit(check, cmd);
	return (NULL);
}
