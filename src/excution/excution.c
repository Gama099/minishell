#include "../../includes/minishell.h"

char    *run_normal(t_command *cmd, t_env_list *env)
{
    char    *command;
    int pid;
    int status;

    command = find_path(env, cmd->argumants[0]);
    if (command == NULL)
        return (NULL);
    if ((pid = fork()) == -1)
    {
        printf("error with fork\n");
        return (NULL);
    }
    else if (pid == 0)
        execve(command, cmd->argumants, NULL);
    else
        wait(&status);
    //free(command);
    return ("succes");
}


void	one_cmd(t_command *cmd, t_env_list *list)
{
	 if (check_if_builts(cmd->argumants[0]) == 0)
            run_builts(cmd->argumants[0], list);
	else
	{
		if (cmd->files.redirec == NULL)
			run_normal(cmd, list);
		// <
		else if (!ft_strncmp(cmd->files.redirec, "redin", INT_MAX))
			redirec_input(cmd, list);
		// >
		else if (!ft_strncmp(cmd->files.redirec, "redout", INT_MAX))
			redirec_out(cmd, list);
		// >>
		else if (!ft_strncmp(cmd->files.redirec, "redapp", INT_MAX))
			redirec_app_out(cmd, list);
		// <<
		else if (!ft_strncmp(cmd->files.redirec, "herdoc", INT_MAX))
			herdoc(cmd);
	}
}

int	excution(t_command *cmd, t_env_list *list)
{
	if (cmd->next == NULL)
		one_cmd(cmd, list);
	while (cmd != NULL)
	{
		
	}
	return (EXIT_SUCCESS);
}
