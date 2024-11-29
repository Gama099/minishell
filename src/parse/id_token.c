/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hadd <sel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:26:50 by sel-hadd          #+#    #+#             */
/*   Updated: 2024/11/29 22:26:52 by sel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_spaces(char *str)
{
	while (*str)
	{
		if (*str == ' ' || (*str >= '\r' && *str <= '\t'))
			str++;
		else
			return (1);
	}
	return (0);
}

void	hanlde_red(t_tokens **current, char *type)
{
	(*current)->tokentype = type;
	if ((*current)->next && !is_operator((*current)->next->token))
	{
		*current = (*current)->next;
		(*current)->tokentype = "file";
	}
}

void	parser(t_tokens **list)
{
	t_tokens	*current;

	current = *list;
	while (current)
	{
		if (current == *list && (checkcommand(current->token)))
			current->tokentype = "command";
		else if (!ft_strcmps(current->token, "|") && !current->qoute_type)
		{
			current->tokentype = "pipe";
			parser(&current->next);
			return ;
		}
		else if (!ft_strcmps(current->token, ">") && !current->qoute_type)
			hanlde_red(&current, ft_strdup("output"));
		else if (!ft_strcmps(current->token, "<") && !current->qoute_type)
			hanlde_red(&current, ft_strdup("input"));
		else if (!ft_strcmps(current->token, ">>") && !current->qoute_type)
			hanlde_red(&current, ft_strdup("appaned"));
		else if (!ft_strcmps(current->token, "<<") && !current->qoute_type)
			hanlde_red(&current, ft_strdup("herdoc"));
		else
			current->tokentype = "argurment";
		current = current->next;
	}
}
