#include "../../includes/minishell.h"

char    *run_normal(t_command *cmd)
{
    char    *cmd;
    int pid;
    int status;

    cmd = find_path(env, cmd->argumants[0]);
    if (cmd == NULL)
        return (NULL);
    if ((pid = fork()) == -1)
    {
        printf("error with fork\n");
        return (NULL);
    }
    else if (pid == 0)
        execve(cmd, cmd->argumants, NULL);
    else
        wait(&status);
    free(cmd);
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
		else if (cmd->files.redirec == "redin")
			redirec_input(cmd);
		else if (cmd->files.redirec == "redout")
			redirec_out(cmd);
		else if (cmd->files.redirec == "redapp")
			redirec_app_out(cmd);
		else if (cmd->files.redirec == "herdoc")
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

}
