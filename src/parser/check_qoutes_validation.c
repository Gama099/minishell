#include "../../includes/minishell.h"


int is_qoute_valid(char *buffer)
{
	int	inQoute;
	char qouteType;

	inQoute = 0;
	qouteType = '\0';
    while (*buffer)
    {
		if ((*buffer == '\'' || *buffer == '\"') && !inQoute)
		{
			inQoute = 1;
			qouteType = *buffer;
		}
		else if(*buffer == qouteType && inQoute)
		{
			inQoute = 0;
			qouteType = '\0';
		}
        buffer++;
    }
	if (inQoute)
		return (inQoute);
	return (0);
}

// int main()
// {
// 	char *str = ft_strdup("\"hello\"");
//     if (!is_qoute_valid(str))
//         printf("valid\n");
//     else
//         printf("invalid\n");
// }
