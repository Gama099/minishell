/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoute.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hadd <sel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:29:18 by sel-hadd          #+#    #+#             */
/*   Updated: 2024/11/29 22:30:36 by sel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_qoute_valid(char *buffer)
{
	int		in_qoute;
	char	qoute_type;

	in_qoute = 0;
	qoute_type = '\0';
	while (*buffer)
	{
		if ((*buffer == '\'' || *buffer == '\"') && !in_qoute)
		{
			in_qoute = 1;
			qoute_type = *buffer;
		}
		else if (*buffer == qoute_type && in_qoute)
		{
			in_qoute = 0;
			qoute_type = '\0';
		}
		buffer++;
	}
	if (in_qoute)
		return (err_msg("enter valid quotes", NULL, NULL), 1);
	return (0);
}
