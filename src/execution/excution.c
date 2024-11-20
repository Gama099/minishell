#include "../../includes/minishell.h"

char	*get_redarct(t_command *cmd, int *pipe, int input)
{
	char	*command;

	if (input != 0)
		ft_dup(input, STDIN_FILENO);
	if (pipe != NULL)
	{
		close(pipe[0]);
		ft_dup(pipe[1], STDOUT_FILENO);
	}
	command = NULL;
	if (check_path(cmd) == 0) //user didnt give path
		command = find_path(cmd->argumants[0]); //find path my self
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
	int		pid;
	char	*command;
	int		status;
	char	**env;

	pid = fork();
	if (pid == -1)
		err_n_exit("error with fork", "fork", NULL, 1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler_cmd);
	//signal(SIGQUIT, sigquit_handler_cmd);
	if (pid == 0)
	{
		child_builtin_helper(cmd, input, pipe); //if not exit from child prossec that mean its not builtin
		command = get_redarct(cmd, pipe, input);
		if (command == NULL) //get path and redirct
			return (pid);
		env = env_to_ary(ft_bash()->list);
		status = execve(command, cmd->argumants, env); //excute the cmd
		if (status == -1)
		{
			perror("error");
			free_ary(env);
			clean_exit(status); //free if execve failed
		}
	}
	return (pid);
}

int	spaces(t_command *cmd)
{
	if (cmd->argumants[0][0] == '\0' || is_white_space(cmd->argumants[0][0]))
		return (1);
	return (0);
}

int	no_cmd(t_command *cmd)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid == -1)
		err_n_exit("syscall failed", "fork", NULL, 1); //exit program
	if (pid == 0)
	{
		redirect_no_cmd(cmd->files);
		exit(0);
	}
	waitpid(pid, &status, 0);
	return ((((status) & 0xff00) >> 8));
}

int	excution(t_command *cmd)
{
	int			status;
	int			pid;

	if (cmd->argumants == NULL)
		return (no_cmd(cmd));
	if (spaces(cmd) == 1)
		return (0);
	if (cmd->next == NULL)
	{
		if (check_if_builts(cmd->argumants[0]) == 0)
			status = builtin_helper(cmd);
		else
		{
			set_under_score(cmd->argumants);
			pid = one_cmd(cmd, 0, NULL);
			waitpid(pid, &status, 0);
		}
	}
	else
		status = excute_pipe(cmd);
	return ((((status) & 0xff00) >> 8));
}
