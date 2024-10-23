#include "minishell.h"

char    *redirec_input(t_command *cmd, t_env_list *env)
{
    int pid;
    int status;
    char *cmd;

    cmd = find_path(env, cmd->argumants[0]);
    if (cmd == NULL)
        return (NULL);
    if ((pid = fork()) == -1)
    {
        printf("error with fork\n");
        return (NULL);
    }
    else if (pid == 0)
    {
        //cmd->files->fd[0] = open(cmd->files->name, O_RDONLY);
        //ft_dup(cmd->files->fd[0], 0);
        execve(cmd, cmd->argumants, NULL);
    } 
    wait(&status);
    return ("succes");
}

char    *redirec_out(t_command *cmd, t_env_list *env)
{
    int pid;
    int status;
    char *cmd;

    cmd = find_path(env, cmd->argumants[0]);
    if (cmd == NULL)
        return (NULL);
    if ((pid = fork()) == -1)
    {
        printf("error with fork\n");
        return (NULL);
    }
    else if (pid == 0)
    {
        //cmd->files->fd[1] = open(cmd->files->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        //ft_dup(cmd->files->fd[1], 1);//output of cmd to outfile fd
        execve(cmd, cmd->argumants, NULL);
    } 
    wait(&status);
    return ("succes");  
}

char    *redirec_app_out(t_command *cmd, t_env_list *env)
{
    int pid;
    int status;
    char *cmd;

    cmd = find_path(env, cmd->argumants[0]);
    if (cmd == NULL)
        return (NULL);
    if ((pid = fork()) == -1)
    {
        printf("error with fork\n");
        return (NULL);
    }
    else if (pid == 0)
    {
        //cmd->files->fd[1] = open(cmd->files->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
        //ft_dup(cmd->files->fd[1], 1);//output of cmd to outfile fd
        execve(cmd, cmd->argumants, NULL);
    } 
    wait(&status);
    return ("succes");  
}