#include "../../includes/minishell.h"


int	is_spaces(char *str)
{
	while (*str)
	{
		if (*str == ' ' || (*str >= '\r' && *str <='\t'))
			str++;
		else
			return (1);
	}
	return (0);
}

void	hanlde_red(t_tokens **current, char *type)
{
	(*current)->tokenType = type;
	if ((*current)->next && !is_operator((*current)->next->token))
    {
        *current = (*current)->next;
        (*current)->tokenType = "file";
    }
}

void    parser(t_tokens **list)
{
    t_tokens    *current;

    current = *list;
    while (current)
    {
       if (current == *list && (checkcommand(current->token)))
            current->tokenType = "command";
        else if (!ft_strcmps(current->token, "|") && !current->qoute_type)
		{
            current->tokenType = "pipe";
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
            current->tokenType = "argurment";
		current = current->next;
    }
}
