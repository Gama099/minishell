#include "../../includes/minishell.h"

int check_access(char *PATH)
{
    if (access(PATH, F_OK) == 0)
    {
        if (access(PATH, X_OK) == 0)
            return (0);
        else
            return (2);
    }
    else
        return (1);      
}

char    *find_path(char **env, char *cmd)
{
    char    **path;
    char    *PATH;
    int i;
    int check;

    i = 0;
    check = 0;
    while ((PATH = ft_strnstr(env[i], "PATH", 4)) == NULL)
        i++;
    path = ft_split(PATH, ':');
    i  = 0;
    cmd = ft_strjoin("/", cmd); 
    while (path[i])
    {
        PATH = ft_strjoin(path[i],cmd);
        check = check_access(PATH);
        if (check == 0)
            return (PATH);
        i++;
    }
    if (check == 1)
        return (write(2, "command not found\n", 19), NULL);
    else if (check == 2)
        return (write(2, "permission denied\n",19), NULL);
    return (NULL);
}

