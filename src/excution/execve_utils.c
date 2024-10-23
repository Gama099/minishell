#include "minishell.h"

int set_under_score(char **argv)
{
    t_env_list *node;
    char    *value;
    int i;

    i = 0;
    while (argv[i])
        i++;
     if (i = 1)
        return (1);
    node = check_if_exit(ft_bash()->list, "_");
    value = node->value;
    node->value = ft_strdup(argv[i - 1]);
    free(value);
    return (0);
}

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

char    *find_path(t_env_list *env, char *cmd)
{
    char    **path;
    char    *splited_path;
    int i;
    int check;

    i = 0;
    check = 0;
    while ((splited_path = ft_strnstr(env->name, "PATH", 4)) == NULL)
        env = env->next;
    path = ft_split(splited_path, ':');
    i  = 0;
    cmd = ft_strjoin("/", cmd); 
    while (path[i])
    {
        splited_path = ft_strjoin(path[i],cmd);
        check = check_access(splited_path);
        if (check == 0)
            return (splited_path);
        i++;
    }
    if (check == 1)
        return (write(2, "command not found\n", 19), NULL);
    else if (check == 2)
        return (write(2, "permission denied\n",19), NULL);
    return (NULL);
}

