#include "../../../includes/minishell.h"

int	check_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1] != '\0')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}



int	check_if_builts(char **argv)
{
    if (!ft_strncmp(argv[1], "echo", INT_MAX))
        return (0);
    else if (!ft_strncmp(argv[1], "pwd", INT_MAX))
        return (0);
	else if (!ft_strncmp(argv[1], "env", INT_MAX))
		return (0);
	else if (!ft_strncmp(argv[1], "export", INT_MAX))
		return (0);
	else if (!ft_strncmp(argv[1], "unset", INT_MAX))
		return (0);
    return (1);
}

void	run_builts(char **argv, int argc, t_env_list *list)
{
    if (!ft_strncmp(argv[1], "echo", INT_MAX))
        ft_echo(argv, argc);
    else if (!ft_strncmp(argv[1], "pwd", INT_MAX))
        ft_pwd();
	else if (!ft_strncmp(argv[1], "env", INT_MAX))
		ft_env(list);
	else if (!ft_strncmp(argv[1], "export", INT_MAX))
		ft_export(list, argv);
	else if (!ft_strncmp(argv[1], "unset", INT_MAX))//to do
		ft_unset(argv, list);
}
