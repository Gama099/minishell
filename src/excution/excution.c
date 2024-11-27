#include "../../includes/minishell.h"

char	*get_redarct(t_command *cmd, int *pipe, int input)
{
	char	*command;

	if (input != 0)
		ft_dup(input, STDIN_FILENO);
	if (pipe != NULL)
	{
		ft_close(pipe[0]);
		ft_dup(pipe[1], STDOUT_FILENO);
	}
	command = NULL;
	if (check_path(cmd) == 0) //user didnt give path
		command = find_path(cmd->args[0]); //find path my self
	else
	{
		redirect_file(cmd);
		return (cmd->args[0]);
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

	signal(SIGINT, sigint_handler_cmd);
	signal(SIGQUIT, sigquit_handler_cmd);
	pid = ft_fork();
	if (pid == 0)
	{
		child_builtin_helper(cmd, input, pipe); //if not exit from child prossec that mean its not builtin
		command = get_redarct(cmd, pipe, input);
		if (command == NULL) //get path and redirct
			err_n_exit("No such file or directory", NULL, cmd->args[0], 127);
		env = env_to_ary(ft_bash()->list);
		status = execve(command, cmd->args, env); //excute the cmd
		if (status == -1)
		{
			free_ary(env);
			clean_exit(1); //free if execve failed
		}
	}
	return (pid);
}

int	spaces(t_command *cmd)
{
	if (cmd->args[0][0] == '\0' || is_white_space(cmd->args[0][0]))
		return (1);
	return (0);
}

int	no_cmd(t_command *cmd)
{
	int		pid;

	if (cmd->files->name == NULL)
		return (ft_bash()->exit_status);
	pid = ft_fork();
	if (pid == 0)
	{
		redirect_no_cmd(cmd->files);
		clean_exit(0);
	}
	return (pid);
}

int	excution(t_command *cmd)
{
	int			status;
	int			pid;

	if (excution_parse(cmd) != 0)
		return (ft_bash()->exit_status);
	if (cmd->next == NULL)
	{
		if (cmd->args == NULL)
		{
			pid = no_cmd(cmd);
			waitpid(pid, &status, 0);
		}
		else if (check_if_builts(cmd->args[0]) == 0)
			return (builtin_helper(cmd));
		else
		{
			set_under_score(cmd->args);
			pid = one_cmd(cmd, 0, NULL);
			waitpid(pid, &status, 0);
		}
	}
	else
		status = excution_pipe(cmd);
	return (excution_status(status));
}
