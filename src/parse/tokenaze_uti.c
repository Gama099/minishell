/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenaze_uti.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hadd <sel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:38:48 by sel-hadd          #+#    #+#             */
/*   Updated: 2024/11/30 01:13:24 by sel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_and_handle_white_space(t_params *params, char *buffer)
{
	if (params->iter > buffer && is_white_space(*params->iter)
		&& *(params->iter - 1) == '\0' && !params->in_qoutes)
		*params->iter = '\0';
	else if (is_white_space(*params->iter) && !params->in_qoutes
		&& *(params->iter - 1) != '\0')
		reach_space(params);
}

void	check_and_handle_quote(t_params *params, int sing_flag, char *buffer)
{
	if ((*params->iter == '\'' || *params->iter == '\"')
		&& !params->in_qoutes && !(sing_flag && *params->iter == '\''))
		start_qoute(params, buffer);
	else if (*params->iter == params->which_qoute && params->in_qoutes)
		close_qoute(params);
}

void	check_and_handle_operator(t_params *params)
{
	if (is_meta(*params->iter) && !params->in_qoutes)
		reach_operator(params);
}

void	check_and_handle_dollar(t_params *params, char *buffer)
{
	if (*params->iter == '$' && !params->in_qoutes)
		reach_dollar(params, buffer);
}

t_tokens	*get_tokens(char *buffer, int sing_flag)
{
	t_params	params;

	trim_spaces(&buffer);
	init_params(&params, buffer);
	while (*params.iter)
	{
		params.to_join = 0;
		if (*params.token_begin == '\0')
			return (params.tokens);
		check_and_handle_white_space(&params, buffer);
		check_and_handle_quote(&params, sing_flag, buffer);
		check_and_handle_operator(&params);
		check_and_handle_dollar(&params, buffer);
		params.iter++;
	}
	if (params.token_begin)
		create_tokens(&params.tokens, params.token_begin, 0, 0);
	return (params.tokens);
}
