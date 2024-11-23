#include "../../includes/minishell.h"

int	ft_check_arg(char **av)
{
	int i;

	i = 1;
	while (av[i])
	{
		if (!ft_strncmp(av[i], "env", INT_MAX))
			i++;
		else
			return (i);
	}
	return (0);
}

void	ft_env_i(void)
{
	char	**env;

	env = (char **)malloc((4) * sizeof(char *));
	if (!env)
		err_n_exit("syscall failed", "malloc", NULL, 1);
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
	if (i != 0)
		return (printf("env: ‘%s’: No such file or directory\n", str[i]), 127);
	while (new_node != NULL)
	{
		if (new_node->type == 1)
		{
			printf("%s", new_node->name);
			printf("=%s\n", new_node->value);
		}
		new_node = new_node->next;
	}
	return (0);
}
