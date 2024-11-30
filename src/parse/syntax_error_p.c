/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_p.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hadd <sel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:43:58 by sel-hadd          #+#    #+#             */
/*   Updated: 2024/11/30 00:23:45 by sel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_special_operator(char *tokentype)
{
	return (!ft_strcmps(tokentype, "output")
		|| !ft_strcmps(tokentype, "input")
		|| !ft_strcmps(tokentype, "appaned")
		|| !ft_strcmps(tokentype, "herdoc"));
}

int	is_operator(char *token)
{
	return (!ft_strcmps(token, "|")
		|| !ft_strcmps(token, ">")
		|| !ft_strcmps(token, "<")
		|| !ft_strcmps(token, ">>")
		|| !ft_strcmps(token, "<<"));
}

int	check_first_token_is_pipe(t_tokens *tokens)
{
	if (!tokens || !ft_strcmps(tokens->tokentype, "pipe"))
	{
		ft_putstr_fd("syntax error near unexpected token ", 2);
		ft_putendl_fd(tokens->token, 2);
		return (2);
	}
	return (0);
}
