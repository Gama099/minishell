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

int	ft_strcmps(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)(*s1) - (unsigned char)(*s2));
		s1++;
		s2++;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

int	syntax_b(t_tokens *prev, t_tokens *tokens)
{
	if (prev && (is_special_operator (prev->tokentype)
			|| !ft_strcmps(prev->tokentype, "pipe")))
	{
		ft_putstr_fd("syntax error near unexpected token ", 2);
		ft_putendl_fd(tokens->token, 2);
		return (2);
	}
	else
		return (0);
}

void	syntax_c(t_tokens *tokens, int mode, char *token_str)
{
	if (mode == 0)
	{
		ft_putstr_fd("syntax error near unexpected token ", 2);
		ft_putendl_fd(tokens->next->token, 2);
	}
	else if (mode == 1)
	{
		err_msg("syntax error near unexpected token`newline' ", NULL, NULL);
	}
	else if (mode == 3)
	{
		ft_putstr_fd("syntax error near unexpected token ", 2);
		ft_putendl_fd(token_str, 2);
	}
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
		if (tokens == start && !ft_strcmps(tokens->tokentype, "pipe"))
			return (syntax_c(NULL, 3, tokens->token), 2);
		else if (!tokens->next && !ft_strcmps(tokens->tokentype, "pipe"))
			return (syntax_c(NULL, 3, tokens->tokentype), 2);
		else if (!tokens->next && is_special_operator(tokens->tokentype))
			return (syntax_c(NULL, 1, NULL), 2);
		else if (!ft_strcmps(tokens->tokentype, "pipe")
			&& (syntax_b(prev, tokens) == 2))
			return (2);
		else if (is_special_operator(tokens->tokentype)
			&& is_special_operator(tokens->next->tokentype))
			return (syntax_c(tokens, 0, NULL), 2);
		prev = tokens;
		tokens = tokens->next;
	}
	return (0);
}
