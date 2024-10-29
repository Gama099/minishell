#include "../../includes/minishell.h"

int	there_is_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i - 1] == '+')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int	check_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1] != '\0')//there is value
			return (EXIT_SUCCESS);
		else if (str[i] == '=' && str[i + 1] == '\0')//null value
			return (2);
		i++;
	}
	return (EXIT_FAILURE);//no =
}

int	before_sum(char *str)
{
	int	j;

	j = 1;
	if (!ft_isalphaa(str[0]) && str[0] != '_')//alpha or underscore
		return (0);
	while (str[j])
	{
		if (!ft_isalnumm(str[j]) && str[j] != '_')//alpha or numeric or underscore
			return (0);
		j++;
	}
	return (1);
}

int	arg_valid(char *str)
{
	char	**splited;

	if (!there_is_plus(str))
	{
		splited = ft_split(str, '+');
		if (before_sum(splited[0]) == 1)//check if var is valid
			return (4);
		else
			return (EXIT_FAILURE);
	}
	else
	{
		splited = ft_split(str, '=');
		if (check_value(str) == 1)
		{
			if (before_sum(splited[0]) == 1)//check if var is valid
				return (5);
		}
		else
		{
			if (before_sum(splited[0]) == 1)
				return (3);
		}
	}
	return (EXIT_FAILURE);
}
