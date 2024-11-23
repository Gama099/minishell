#include "../../includes/minishell.h"


// typedef struct s_tokens
// {
// 	char *token;
// 	struct s_tokens *next;
// } t_tokens;

int	is_meta(char c)
{
	return (c == '>' || c == '<' || c == '|' );
}

void	createTokensmeta(t_tokens **token, char str)
{
	t_tokens	*newNode = malloc(sizeof(t_tokens));
	t_tokens	*last = NULL;

	if (str == '>')
		newNode->token = ft_strdup(">");
	if (str == '<')
		newNode->token = ft_strdup("<");
	if (str == '|')
		newNode->token = ft_strdup("|");
	newNode->next = NULL;
	newNode->qoute_type = 0;
	newNode->tokenType = NULL;
	newNode->join_with_next = 0;
	if (!*token)
		*token = newNode;
	else
	{
		last = *token;
		while (last->next)
			last = last->next;
		last->next = newNode;
	}
	return ;
}



void	createTokens(t_tokens **token, char *str, int qoute, int to_join)
{
	t_tokens	*newNode = malloc(sizeof(t_tokens));
	t_tokens	*last = NULL;
	newNode->token = ft_strdup(str);
	newNode->next = NULL;
	newNode->qoute_type = qoute;
	newNode->join_with_next = to_join;
	newNode->tokenType = NULL;
	newNode->expand_env = 0;
	if (!*token)
		*token = newNode;
	else
	{
		last = *token;
		while (last->next)
			last = last->next;
		last->next = newNode;
	}
	return ;
}

void	token_meta(t_tokens **token, char **iter, char **tokenBegin, char *start);

t_tokens *getTokens(char *buffer)
{
	char 		*iter;
	int			inQoutes = 0;
	char		whichQoute = '\0';
	char		*tokenBegin;
	char		tmp_meta;
    t_tokens *tokens = NULL;

	int to_join;

	trimSpaces(&buffer);
    iter = buffer;
    tokenBegin = buffer;
	if (is_qoute_valid(buffer))
    {
		//exit function and enum ERR_INVALID_QOUTES
		printf("not valid\n");
		return (NULL);
    }
	while (*iter)
	{
		// frist thin is to check the joining flag and reset it
		//if (the things has to be colling)
		//{ set join with 1
		//}
		to_join = 0;
		// tokenbeging is the ptr that passed as the start of the toknen
		if (*tokenBegin == '\0')
			return tokens;
		// this is for this ' ' ' ' ' ' to become this '/0' '/0' '/0' '/0'
		if (iter > buffer && (is_white_space(*iter) && *(iter - 1) == '\0') && !inQoutes){
			*iter = '\0';
		}
		// the start of a qoute
		else if ((*iter == '\'' || *iter == '\"') && !inQoutes){
			inQoutes = 1;
			whichQoute = *iter;
			*iter = '\0';
			if ((iter - 1) >= buffer && *(iter - 1))
				createTokens(&tokens, tokenBegin, 0, 1);
			tokenBegin = iter + 1;
		}
		// echo hello"world";

		// when there's space out side of the qoute it do
		// set to '\0' then
		// create the token and give the 0 as a flag for envirement varibles
		//
		else if ((*iter == ' ' && !inQoutes) && *(iter - 1) != '\0'){
			*iter = '\0';
			createTokens(&tokens, tokenBegin, 0, to_join);
			tokenBegin = iter + 1;
			if (*tokenBegin == '\0')
				return tokens;
			else {

			while (is_white_space(*tokenBegin))
				tokenBegin++;
			}
		}
		// the close of that qoute
		else if ((*iter == whichQoute && inQoutes))
		{
			if (*(iter + 1) && !is_white_space(*(iter + 1)))
			//if (*(iter + 1) == '\'' || *(iter + 1) == '\"')
			{
				to_join = 1;
			}
			*iter = '\0';
			// single qoute ' = 1
			if (whichQoute == '\'')
				createTokens(&tokens, tokenBegin, 1, to_join);
			else
				createTokens(&tokens, tokenBegin, 2, to_join);
			tokenBegin = iter + 1;
			if (*tokenBegin == '\0')
				return tokens;
			else {
			while (is_white_space(*tokenBegin))
				tokenBegin++;
			}
			inQoutes = 0;
		}
		// when we are at
		else if (is_meta(*iter) && !inQoutes)
		{
			token_meta(&tokens, &iter, &tokenBegin, buffer);
			if (*tokenBegin == '\0')
				return tokens;
			/*tmp_meta = *iter;
			if (*(iter - 1))
			{
				*iter = '\0';
				createTokens(&tokens, tokenBegin, 0);
			}
			*iter = '\0';
			createTokensmeta(&tokens, tmp_meta);
			tokenBegin = iter + 1;
			if (*tokenBegin == '\0')
				return tokens;
			else {
			while (is_white_space(*tokenBegin))
				tokenBegin++;
			}*/
		}
		else if (*iter == '$' && !inQoutes)
		{
			if ((iter - 1) >= buffer && *(iter - 1))
			{
			*iter = '\0';
			createTokens(&tokens, tokenBegin, 0, 1);
			*iter = '$';
			tokenBegin = iter;
			}
		}
		iter++;
	}
	if (tokenBegin)
		createTokens(&tokens, tokenBegin, 0, 0);
	return tokens;
}


void	token_meta(t_tokens **token, char **iter, char **tokenBegin, char *start)
{
	char tmp_iter;

	tmp_iter = **iter;
	if (start <= (*iter - 1) && *(*iter - 1))
	{
		**iter = '\0';
		createTokens(token, *tokenBegin, 0, 0);
		**iter = tmp_iter;
	}
	**iter = tmp_iter;
	if (**iter == '>' && *(*iter + 1) == '>')
	{
		createTokens(token, ">>", 0, 0);
		(*iter)++;
	}
	else if (**iter == '<' && *(*iter + 1) == '<')
	{
		createTokens(token, "<<", 0, 0);
		(*iter)++;
	}
	else if (**iter == '>')
		createTokens(token, ">", 0, 0);
	else if (**iter == '<')
		createTokens(token, "<", 0, 0);
	else if (**iter == '|')
		createTokens(token, "|", 0, 0);
	**iter = '\0';
	*tokenBegin = (*iter + 1);
	//printf("tokebegin at iter + 1 %s\n", *tokenBegin);
	if (**tokenBegin == '\0')
		return ;
	else{
		while (is_white_space(**tokenBegin))
				(*tokenBegin)++;
		}
	//printf("tokebegin at iter + 100 %s\n", *tokenBegin);
}
