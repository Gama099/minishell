#include "minishell.h"

int	is_a_directory(char *filename, int bltn)
{
	struct stat	buff;

	ft_bzero(&buff, sizeof(buff));
	stat(filename, &buff);
	if ((buff.st_mode & __S_IFMT) == __S_IFDIR)
	{
		printf("Is a directory");
		if (bltn == 0)
			exit(1);//free todo
		return (1);
	}
	return (0);
}

int	check_path(t_command *cmd)
{
	int	check;

	check = 0;
	if (ft_strchrr(cmd->argumants[0], '/') != -1)
	{
		if (is_a_directory(cmd->argumants[0], 1))
			exit(126);
		check = check_access(cmd->argumants[0]);
		if (check == 1)
        	return (write(2, "command not found\n", 19), 1);
    	else if (check == 2)
        	return (write(2, "permission denied\n",19), 1);
	}
	return (check);
}

int	run_normal(t_command *cmd)
{
    char    *command;
    int pid;
    int status;

	command == NULL;
	if (check_path(cmd) == 0);//user didnt give path
		command = find_path(ft_bash()->list, cmd->argumants[0]);//find path my self
    if (command == NULL)
        return (1);
    if ((pid = fork()) == -1)
        return (printf("error with fork\n"), 1);
    else if (pid == 0)
	{
		redirect_file(cmd);
        execve(command, cmd->argumants, NULL);
	}
    else
        wait(&status);
    return (0);
}

int	one_cmd(t_command *cmd)
{
	int	status;

	status = 0;
	if (check_if_builts(cmd->argumants[0]) == 0)
        status = run_builts(cmd);
	else
		status = run_normal(cmd);
	return (status);
}

int	excution(t_command *cmd)
{
	int	*fd;

	if (cmd->next == NULL)
		one_cmd(cmd);
	while (cmd != NULL)
	{
		if (pipe(fd) == -1)
			return (perror("pipe"), 1);
		
	}
	return (0);
}
