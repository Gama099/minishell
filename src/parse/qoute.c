#include "../../includes/minishell.h"

int is_qoute_valid(char *buffer)
{
	int	in_qoute;
	char qoute_type;

	in_qoute = 0;
	qoute_type = '\0';
    while (*buffer)
    {
		if ((*buffer == '\'' || *buffer == '\"') && !in_qoute)
		{
			in_qoute = 1;
			qoute_type = *buffer;
		}
		else if(*buffer == qoute_type && in_qoute)
		{
			in_qoute = 0;
			qoute_type = '\0';
		}
        buffer++;
    }
	if (in_qoute)
		return (in_qoute);
	return (0);
}
