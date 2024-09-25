#include "../../../includes/minishell.h"

char    *ft_echo(char **argv , int argc)
{
    int i;
	int	flag;

    i = echo_check(argv, argc);
	if (i == 2)
		flag = 1;
	else
		flag = 0;
    while (i < argc)
    {
        printf("%s",argv[i]);
        i++;
		if (i != argc)
			printf(" ");
    }
	if (flag == 1)
		printf("\n");
    return ("succes");
}
