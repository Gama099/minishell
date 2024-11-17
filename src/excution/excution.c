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
	signal(SIGINT, sigint_handler_cmd);
	signal(SIGQUIT, sigquit_handler_cmd);
	if (pid == 0)
	{
		env = env_to_ary(ft_bash()->list);
		child_builtin_helper(cmd, input, pipe); //if not exit from child prossec that mean its not builtin
		command = get_redarct(cmd, pipe, input);
		if (command == NULL) //get path and redirct
			return (free_ary(env), pid);
		status = execve(command, cmd->argumants, env); //excute the cmd
		if (status == -1)
		{
			free_ary(env);
			clean_exit(status); //free if execve failed
		}
	}
	return (pid);
}

int	excution(t_command *cmd)
{
	int			status;
	int			pid;

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
	return (status);
}
