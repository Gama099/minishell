#include "../../includes/minishell.h"

int    check_if_builts(char *arg)
{
    if (strcmp(arg, "echo") == 0)
        return (0);
    else if (strcmp(arg, "pwd") == 0)
        return (0);
    return (1);
}

void    run_builts(char *arg)
{
    if (strcmp(arg, "echo") == 0)
        ft_echo();
    else if (strcmp(arg, "pwd") == 0)
        ft_pwd();
}
