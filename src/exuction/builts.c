#include "../../includes/minishell.h"



int ft_pwd()
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    if (pwd == NULL)
        return (EXIT_FAILURE);
    printf("%s\n",pwd);
    free (pwd);
    return (EXIT_SUCCESS);
}
