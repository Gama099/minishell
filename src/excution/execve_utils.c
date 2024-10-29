#include "../../includes/minishell.h"

int set_under_score(char **argv)
{
    t_env_list *node;
    char    *value;
    int i;

    i = 0;
    while (argv[i])
        i++;
     if (i == 1)
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
	char	*tmp;
    int i;
    int check;

    i = 0;
    check = 0;
    while ((splited_path = ft_strnstr(env->name, "PATH", 4)) == NULL)
        env = env->next;
    path = ft_split(splited_path, ':');
    i  = 0;
    tmp = ft_strjoin("/", cmd);
    while (path[i])
    {
        splited_path = ft_strjoin(path[i],tmp);
        check = check_access(splited_path);
        if (check == 0)
            return (splited_path);
        i++;
    }
    if (check == 1)
		err_n_exit("command not found", NULL, cmd, 127);
    else if (check == 2)
        err_n_exit("permission denied", NULL, cmd, 126);
    return (NULL);
}
