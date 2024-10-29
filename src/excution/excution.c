#include "../../includes/minishell.h"

int	check_path(t_command *cmd)
{
	int	check;

	check = 0;
	if (ft_strchrr(cmd->argumants[0], '/') != -1)
	{
		if (is_a_directory(cmd->argumants[0], 1))
			clean_exit(126);
		check = check_access(cmd->argumants[0]);
		if (check == 1)// not found
        	err_n_exit(NULL, NULL, cmd->argumants[0], 127);
    	else if (check == 2)//not excutable
        	err_n_exit(NULL, NULL, cmd->argumants[0], 126);
		else
			return (3);//path is valid
	}
	return (check);
}

char	*get_redarct(t_command *cmd)
{
    char    *command;

	command = NULL;
	if (check_path(cmd) == 0)//user didnt give path
		command = find_path(cmd->argumants[0]);//find path my self
	else
	{
		redirect_file(cmd);
		return (cmd->argumants[0]);
	}
	redirect_file(cmd);
    return (command);
}

void	one_cmd(t_command *cmd)
{
	int 	pid;
	int		child_status;
	char    *command;

	//i will try to put everything in child prossec
	if ((pid = fork()) == -1)
        err_n_exit("error with fork", "fork", NULL, 1);
	if (pid == 0)
	{
        child_builtin_helper(cmd);//if not exit from child prossec that mean its not builtin
		command = get_redarct(cmd);//get path and redirct
		execve(command, cmd->argumants, NULL);//excute the cmd
	}
	wait(&child_status);
}

int	excution(t_command *cmd)
{
	//int	*fd;

	if (cmd->next == NULL && check_if_builts(cmd->argumants[0]) == 0)
		builtin_helper(cmd);
	else
		one_cmd(cmd);
	// while (cmd != NULL)
	// {
	// 	if (pipe(fd) == -1)
	// 		return (perror("pipe"), 1);

	// }
	return (0);
}
