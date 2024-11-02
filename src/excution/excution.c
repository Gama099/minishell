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

char	*get_redarct(t_command *cmd, int *pipe, int input)
{
    char    *command;

	if (input != 0)
		ft_dup(input, STDIN_FILENO);
	if (pipe != NULL)
    {
    	close(pipe[0]);
		ft_dup(pipe[1], STDOUT_FILENO);
    }
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

int	one_cmd(t_command *cmd, int input, int *pipe)
{
	int 	pid;
	char    *command;

	if ((pid = fork()) == -1)
        err_n_exit("error with fork", "fork", NULL, 1);
	if (pid == 0)
	{
        child_builtin_helper(cmd, input, pipe);//if not exit from child prossec that mean its not builtin
		command = get_redarct(cmd, pipe, input);//get path and redirct
		execve(command, cmd->argumants, ft_bash()->env);//excute the cmd
	}
	return (pid);
}

int	count_pipe(t_command *cmd)
{
	int	i;

	i = 0;
	while(cmd->next != NULL)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

int ft_wait(int j, int *pid)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (i < j)
		waitpid(pid[i++], &status, 0);
	free(pid);
	return (status);
}

int	excute_pipe(t_command *cmd)
{
	int	fd[2];
	int	old_input;
	int *pid;
	int	i;
	int	j;

	i = 0;
	old_input = 0;
	j = count_pipe(cmd);
	pid = malloc(sizeof(int) * (j + 1));
	if (pid == NULL)
		err_n_exit("syscall failed", "malloc", NULL, 1);
	while (cmd != NULL)
	{
		if (cmd->next != NULL)
		{
			if (pipe(fd) == -1)
				err_n_exit("syscall failed", "pipe", NULL, 1);
		}
		if (cmd->next == NULL)
			pid[i] = one_cmd(cmd, old_input, NULL);
		else
			pid[i] = one_cmd(cmd, old_input, fd);
		if (old_input != 0)
			close (old_input);
		if (cmd->next != NULL)
		{
			old_input = fd[0];
			close (fd[1]);
		}
		cmd = cmd->next;
		i++;
	}
	return (ft_wait(j, pid));
}

int	excution(t_command *cmd)
{
	int status;
	int pid;

	if (cmd->next == NULL)
	{
		if (check_if_builts(cmd->argumants[0]) == 0)
			builtin_helper(cmd);
		else
		{
			pid = one_cmd(cmd, 0, NULL);
			waitpid(pid, &status, 0);
		}
	}
	else
		status = excute_pipe(cmd);
	return (status);
}
