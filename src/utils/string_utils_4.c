#include "../../includes/minishell.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}

t_tokens	*get_tokens_herdoc(char *buffer, int sing_flag, int dbl)
{
	t_params	params;

	trim_spaces(&buffer);
	init_params(&params, buffer);
	while (*params.iter)
	{
		params.to_join = 0;
		if (*params.token_begin == '\0')
			return (params.tokens);
		if ((params.iter > buffer && (is_white_space(*params.iter)
					&& *(params.iter - 1) == '\0') && !params.in_qoutes))
			*params.iter = '\0';
		else if ((*params.iter == '\'') && !params.in_qoutes && !sing_flag)
			start_qoute(&params, buffer);
		else if ((*params.iter == '\"') && !params.in_qoutes && !dbl)
			start_qoute(&params, buffer);
		else if ((is_white_space(*params.iter) && !params.in_qoutes)
			&& *(params.iter - 1) != '\0')
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

char	*expand_herdoc(char *str)
{
	char		*tmp;
	t_tokens	*tokens;

	tmp = NULL;
	tokens = get_tokens_herdoc(str, 1, 1);
	for (t_tokens *i = tokens; i ; i = i->next)
	{
		dprintf(2,"hadi lawal = %s\n", i->token);
	}
	expand_varibles(&tokens);
	for (t_tokens *i = tokens; i ; i = i->next)
	{
		dprintf(2,"hadi tanya = %s\n", i->token);
	}
	while (tokens != NULL)
	{
		tmp = ft_strjoin(tmp, tokens->token);
		if (tokens->token != NULL)
			tmp = ft_strjoin(tmp, " ");
		tokens = tokens->next;
	}
	return (tmp);
}
