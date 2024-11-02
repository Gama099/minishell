#include "../../includes/minishell.h"

void	ft_env_i(void)
{
	// char	**env;
	// char	*pwd;

	// pwd = getcwd(NULL, 0);
	// env = (char **)malloc(sizeof(char *) * 4);
	// env[3] = NULL;
	// env[2] = ft_strjoin(ft_strdup("PWD="), pwd);
	// env[1] = ft_strdup("SHLVL=1");
	// env[0] = ft_strdup("_=/usr/bin/env");
	// ft_bash()->list = env_to_list(env);
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
	i = 0;
	while (str[i])
		i++;
	if (i > 1)
		return (printf("too many arguments\n"), 1);
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
