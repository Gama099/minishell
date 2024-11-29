/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hadd <sel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:43:58 by sel-hadd          #+#    #+#             */
/*   Updated: 2024/11/30 00:09:35 by sel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_last_token_is_pipe(t_tokens *tokens)
{
	if (!tokens->next && !ft_strcmps(tokens->tokentype, "pipe"))
	{
		ft_putstr_fd("syntax error near unexpected token ", 2);
		ft_putendl_fd(tokens->token, 2);
		return (2);
	}
	return (0);
}

int	check_special_operator_is_last(t_tokens *tokens)
{
	if (!tokens->next && is_special_operator(tokens->tokentype))
	{
		return (err_msg("syntax error near unexpected token `newline' ",
				NULL, NULL), 2);
	}
	return (0);
}

int	check_pipe_follows_special_or_pipe(t_tokens *tokens, t_tokens *prev)
{
	if (!ft_strcmps(tokens->tokentype, "pipe"))
	{
		if (prev && (is_special_red(prev->tokentype)
				|| !ft_strcmps(prev->tokentype, "pipe")))
		{
			ft_putstr_fd("syntax error near unexpected token ", 2);
			ft_putendl_fd(tokens->token, 2);
			return (2);
		}
	}
	return (0);
}

int	check_special_operators_adjacent(t_tokens *tokens)
{
	if (is_special_operator(tokens->tokentype)
		&& is_special_operator(tokens->next->tokentype))
	{
		ft_putstr_fd("syntax error near unexpected token ", 2);
		ft_putendl_fd(tokens->next->token, 2);
		return (2);
	}
	return (0);
}

int	handle_syntax_errors(t_tokens *tokens)
{
	t_tokens	*start;
	t_tokens	*prev;

	prev = NULL;
	if (!tokens)
		return (0);
	start = tokens;
	while (tokens)
	{
		if (check_first_token_is_pipe(tokens) == 2)
			return (2);
		if (check_last_token_is_pipe(tokens) == 2)
			return (2);
		if (check_special_operator_is_last(tokens) == 2)
			return (2);
		if (check_pipe_follows_special_or_pipe(tokens, prev) == 2)
			return (2);
		if (check_special_operators_adjacent(tokens) == 2)
			return (2);
		prev = tokens;
		tokens = tokens->next;
	}
	return (0);
}
