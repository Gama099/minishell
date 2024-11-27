#include "../../includes/minishell.h"

int	is_meta(char c)
{
	return (c == '>' || c == '<' || c == '|' );
}

int	is_qoute(char c)
{
	return (c == '\'' || c == '\"');
}

void	start_qoute(t_params *parmas, char *buffer)
{
	parmas->in_qoutes = 1;
	parmas->which_qoute = *parmas->iter;
	*parmas->iter = '\0';
	if ((parmas->iter - 1) >= buffer && *(parmas->iter - 1))
		create_tokens(&parmas->tokens, parmas->token_begin, 0, 1);
	parmas->token_begin = parmas->iter + 1;
}

void	reach_space(t_params *params)
{
	*params->iter = '\0';
	create_tokens(&params->tokens, params->token_begin, 0, params->to_join);
	params->token_begin = params->iter + 1;
	if (*params->token_begin == '\0')
		return ;
	while (is_white_space(*params->token_begin))
		params->token_begin++;
}
