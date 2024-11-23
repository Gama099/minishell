#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char		*pwd;
	t_env_list	*node;
	
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		node = check_if_exit(ft_bash()->list, "PWD", 1);
		printf("%s\n", node->value);
		return (EXIT_SUCCESS);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
