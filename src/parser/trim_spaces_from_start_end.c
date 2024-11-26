#include "../../includes/minishell.h"


int	is_white_space(char charac)
{
	if (charac == ' ' || (charac >= '\t' && charac <= '\r'))
		return (1);
	return (0);
}

void	trimSpaces(char **buffer)
{
	char	*start;
	char	*end;
	int		len;
	char	*newStr;

	if (!*buffer[0]) // for empty line so u dont get error in is is_white_space(start[len - 1])
		return ;
	start = *buffer;
	len = ft_strlen(start);
	if ((!is_white_space(*start) && !is_white_space(start[len - 1])) || !len)
		return ;
	end = &start[len - 1];
	while (is_white_space(*start))
		start++;
	if (!start)
		return ;
	while (is_white_space(*end) && end > start)
		end--;
	newStr = malloc(end - start + 2);
	if (!newStr)
		return ;
	ft_strlcpy(newStr, start, (end - start) + 2);
	free (*buffer);
	*buffer = newStr;
}

