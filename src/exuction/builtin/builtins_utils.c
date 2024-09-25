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

int	echo_check(char **argv, int argc)
{
	int	i;
	int	j;

	i = 2;

	while (i < argc)
	{
		j = 1;
		if (argv[i][0] == '-')
		{
			while (argv[i][j])
			{
				if (argv[i][j] == 'n')
					j++;
				else
					return (i);
			}
		}
		else
			return (i);
		i++;
	}
	return (i);
}

int    check_if_builts(char **argv)
{
    if (strcmp(argv[1], "echo") == 0)
        return (0);
    else if (strcmp(argv[1], "pwd") == 0)
        return (0);
	else if (strcmp(argv[1], "env") == 0)
		return (0);
	else if (strcmp(argv[1], "export") == 0)
		return (0);
	else if (strcmp(argv[1], "unset") == 0)
		return (0);
    return (1);
}

void    run_builts(char **argv, int argc, t_env_list *list)
{
    if (strcmp(argv[1], "echo") == 0)
        ft_echo(argv, argc);
    else if (strcmp(argv[1], "pwd") == 0)
        ft_pwd();
	else if (strcmp(argv[1], "env") == 0)
		ft_env(list);
	else if (strcmp(argv[1], "export") == 0)
		ft_export(list, argv);
	else if (strcmp(argv[1], "unset") == 0)//to do
		ft_unset(argv, list);
}
