/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:13:08 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:13:09 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	there_is_plus(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=')
		return (EXIT_FAILURE);
	while (str[i])
	{
		if (str[i] == '=' && str[i - 1] == '+')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int	before_sum(char *str)
{
	int	j;

	j = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[j])
	{
		if (!ft_isalnum(str[j]) && str[j] != '_')
			return (0);
		j++;
	}
	return (1);
}

int	valid_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] != '=')
			return (1);
		i++;
	}
	return (0);
}

int	arg_helper(char *str)
{
	char	**splited;

	if (valid_plus(str) == 1)
		return (EXIT_FAILURE);
	splited = ft_split(str, '+');
	if (before_sum(splited[0]) == 1)
	{
		if (check_value(str) == 2)
			return (5);
		else
			return (4);
	}
	else
		return (EXIT_FAILURE);
}

int	arg_valid(char *str)
{
	char	**splited;

	if (!str[0])
		return (EXIT_FAILURE);
	if (!there_is_plus(str))
		return (arg_helper(str));
	else
	{
		if (str[0] == '=')
			return (EXIT_FAILURE);
		splited = ft_split(str, '=');
		if (check_value(str) == 1)
		{
			if (before_sum(splited[0]) == 1)
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
