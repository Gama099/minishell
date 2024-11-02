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
	//MALLOC1
	newStr = malloc(end - start + 1);
	//TODO: handle error //buffer maybe i can exit from here and clean up
	//and add the the exit function can have enum ERRMALLOC
	if (!newStr)
		return ;
	ft_strlcpy(newStr, start, (end - start) + 2);
	//free using
	free (*buffer);
	*buffer = newStr;
}

// int main()
// {
// 	char *str = ft_strdup("ff     ");
// 	trimSpaces(&str);
// 	printf("[%s]\n", str);
// }
