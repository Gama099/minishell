#include "../../includes/minishell.h"

void	close_qoute(t_params *params)
{
	if (*(params->iter + 1) && !is_white_space(*(params->iter + 1)))
		params->to_join = 1;
	*params->iter = '\0';
	if (params->which_qoute == '\'')
		create_tokens(&params->tokens, params->token_begin, 1, params->to_join);
	else
		create_tokens(&params->tokens, params->token_begin, 2, params->to_join);
	params->token_begin = params->iter + 1;
	if (*params->token_begin == '\0')
		return ;
	while (is_white_space(*params->token_begin))
		params->token_begin++;
	params->in_qoutes = 0;
}

void	reach_operator_a(t_params *params, char tmp)
{
	*params->iter = '\0';
	create_tokens(&params->tokens, params->token_begin, 0, 0);
	*params->iter = tmp;
}

void	reach_operator_b(t_params *params)
{
	create_tokens(&params->tokens, ">>", 0, 0);
	params->iter++;
}

void	reach_operator(t_params *params)
{
	char	tmp_iter;

	tmp_iter = *params->iter;
	if (params->iter > params->token_begin && *(params->iter - 1))
		reach_operator_a(params, tmp_iter);
	if (*params->iter == '>' && *(params->iter + 1) == '>')
		reach_operator_b(params);
	else if (*params->iter == '<' && *(params->iter + 1) == '<')
		reach_operator_b(params);
	else if (*params->iter == '>')
		create_tokens(&params->tokens, ">", 0, 0);
	else if (*params->iter == '<')
		create_tokens(&params->tokens, "<", 0, 0);
	else if (*params->iter == '|')
		create_tokens(&params->tokens, "|", 0, 0);
	*params->iter = '\0';
	params->token_begin = params->iter + 1;
	if (*params->token_begin == '\0')
		return ;
	else
	{
		while (is_white_space(*params->token_begin))
			params->token_begin++;
	}
}

void	reach_dollar(t_params *params, char *buffer)
{
	if ((params->iter - 1) >= buffer && *(params->iter - 1))
	{
		*params->iter = '\0';
		create_tokens(&params->tokens, params->token_begin, 0, 1);
		*params->iter = '$';
		params->token_begin = params->iter;
	}
	if (*(params->iter + 1) == '?')
	{
		if (*(params->iter + 2) && !is_white_space(*(params->iter + 1)))
			params->to_join = 1;
		create_tokens(&params->tokens, "$?", 0, params->to_join);
		params->token_begin = params->iter + 2;
		params->iter = params->iter + 2;
		if (*params->token_begin == '\0' || *params->iter == '\0')
			return ;
		while (is_white_space(*params->token_begin))
			params->token_begin++;
		while (is_white_space(*params->iter))
			params->iter++;
	}
}