/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:12:56 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:12:57 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit_helper(int exit_code)
{
	if (exit_code < 0)
	{
		while (exit_code < 0)
			exit_code += 256;
	}
	else
	{
		while (exit_code > 256)
			exit_code -= 256;
	}
	clean_exit(exit_code);
	return (1);
}

int	str_is_digit(char *a)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (a[i])
	{
		if ((a[0] == '+' || a[0] == '-') && flag == 0)
		{
			flag = 1;
			i++;
		}
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
	if (arg[i] == NULL)
		ft_exit_helper(ft_bash()->exit_status);
	while (arg[i])
	{
		if (i > 1)
			return (err_msg("too many arguments", "exit", NULL), 1);
		if (str_is_digit(arg[i]) == 1 || arg[i][0] == '\0')
		{
			err_msg("numeric argument required", "exit", arg[i]);
			clean_exit(2);
		}
		i++;
	}
	return (ft_exit_helper(ft_atoi(arg[1])));
}
