//exit without arg
//exit with abc
//exit with too much args
//exit with number bettwen 0 and 255
//others undifiend behavior
#include "minishell.h"

int	ft_exit_helper(int exit_code)
{
	clean_exit(exit_code);
	return (1);
}

int	str_is_digit(char *a)
{
	int	i;

	i = 0;
	while(a[i])
	{
		if (a[i] < '0' || a[i] > '9')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_exit(char **arg)
{
	int	i;

	i = 1;
	write(1, "exit\n", 6);
	if (ft_bash()->cmd.argumants[i] == NULL)//one arg = exit
		ft_exit_helper(0);
	while (arg[i])
	{
		if (i > 1)
			return (printf("too many arguments\n"), 1);
		if (str_is_digit(arg[i]) == 1)
		{
			printf("numeric argument required\n");
			exit(2);//free to do
		}
		i++;
	}
	return (ft_exit_helper(ft_atoi(arg[1])));//second arg = exit 10
}
