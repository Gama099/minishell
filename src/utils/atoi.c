/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:13:56 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:13:57 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isdigit(char a)
{
	if (a < '0' || a > '9')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	cheking_int(char *str, int i)
{
	if (str[i] == '\0')
		return (EXIT_FAILURE);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_atoi(char *str)
{
	int		sign;
	long	res;
	int		i;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (cheking_int(str, i) == 1)
		return (-1);
	while (str[i])
	{
		res = res * 10 +(str[i] - 48);
		i++;
	}
	return (res * sign);
}
