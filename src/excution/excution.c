#include "../../includes/minishell.h"

char    *run_normal(t_command *cmd)
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
    free(command);
    return ("succes");
}


void	one_cmd(t_command *cmd)
{
	 if (check_if_builts(cmd->argumants[0]) == 0)
            run_builts(cmd->argumants[0]);
	else
	{
		if (cmd->files.redirec == NULL)
			run_normal(cmd);
		// <
		else if (ft_strcmp(cmd->files.redirec, "redin") == 0)
			redirec_input(cmd);
		// >
		else if (ft_strcmp(cmd->files.redirec, "redout") == 0)
			redirec_out(cmd);
		// >>
		else if (ft_strcmp(cmd->files.redirec, "redapp") == 0)
			redirec_app_out(cmd);
		// <<
		else if (ft_strcmp(cmd->files.redirec, "herdoc") == 0)
			herdoc(cmd);
	}
}

int	excution(t_command *cmd)
{
	if (cmd->next == NULL)
		one_cmd(cmd);
	while (cmd != NULL)
	{

	}
	return (EXIT_SUCCESS);
}
