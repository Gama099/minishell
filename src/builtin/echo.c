#include "../../includes/minishell.h"

int	echo_check(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 1;
		if (argv[i][0] == '-' && ft_strlen(argv[i]) > 1)
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

int	ft_echo(char **argv)
{
	int		i;
	int		flag;
	char	*str;

	i = echo_check(argv);
	flag = 0;
	if (i == 1) //no -n option
		flag = 1;
	while (argv[i])
	{
		if (argv[i][0] == '$' && argv[i][1] == '?') // tmp
		{
			str = ft_itoa(ft_bash()->exit_status);
			write(1, str, ft_strlen(str));
			ft_putstr_fd(argv[i] + 2, 1);
			free(str);
		}
		else
			write(1, argv[i], ft_strlen(argv[i]));
		i++;
		if (argv[i])
			write(1, " ", 1);
	}
	if (flag == 1)
		write(1, "\n", 1);
	return (0);
}
