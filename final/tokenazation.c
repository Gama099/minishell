#include "parsing.h"


void	create_tokens(t_tokens **token, char *str, int qoute, int to_join)
{
	t_tokens	*new_node;
	t_tokens	*last;

    new_node = malloc(sizeof(t_tokens));
    if (!new_node)
        return ;
    new_node->token = ft_strdup(str);
    if (!new_node->token)
        return;
    new_node->next = NULL;
    new_node->qoute_type = qoute;
    new_node->join_with_next = to_join;
    new_node->tokenType = NULL;
    new_node->expand_env = 0;
    if (!*token)
        *token = new_node;
    else
	{
        last = *token;
        while (last->next)
            last = last->next;
        last->next = new_node;
    }
    return ;
}

void	init_params(t_params *params, char *buffer)
{
	params->iter = buffer;
    params->token_begin = buffer;
    params->in_qoutes = 0;
    params->which_qoute = '\0';
    params->tokens = NULL;
    params->to_join = 0;
}

t_tokens	*get_tokens(char *buffer)
{
	t_params	params;

	trim_spaces(&buffer);
	init_params(&params, buffer);
	while (*params.iter)
	{
		if (*params.token_begin == '\0')
			return (params.tokens);
		if ((params.iter > buffer && (is_white_space(*params.iter) && *(params.iter - 1) == '\0') && !params.in_qoutes))
			*params.iter = '\0';
		else if (is_qoute(*params.iter) && !params.in_qoutes)
			start_qoute(&params, buffer);
		else if ((*params.iter == ' ' && !params.in_qoutes) && *(params.iter - 1) != '\0')
			reach_space(&params);
		else if ((*params.iter == params.which_qoute) && params.in_qoutes)
			close_qoute(&params);
		else if (is_meta(*params.iter) && !params.in_qoutes)
			reach_operator(&params);
		else if (*params.iter == '$' && !params.in_qoutes)
			reach_dollar(&params, buffer);
		params.iter++;
	}
	if (params.token_begin)
		create_tokens(&params.tokens, params.token_begin, 0, 0);
	return (params.tokens);
}
