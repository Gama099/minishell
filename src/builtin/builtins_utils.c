#include "../../includes/minishell.h"

int	check_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1] != '\0') //there is value
			return (EXIT_SUCCESS);
		else if (str[i] == '=' && str[i + 1] == '\0') //null value
			return (2);
		i++;
	}
	return (EXIT_FAILURE);//no =
}

int	check_if_builts(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", INT_MAX))
		return (0);
	else if (!ft_strncmp(cmd, "pwd", INT_MAX))
		return (0);
	else if (!ft_strncmp(cmd, "env", INT_MAX))
		return (0);
	else if (!ft_strncmp(cmd, "export", INT_MAX))
		return (0);
	else if (!ft_strncmp(cmd, "unset", INT_MAX))
		return (0);
	else if (!ft_strncmp(cmd, "exit", INT_MAX))
		return (0);
	else if (!ft_strncmp(cmd, "cd", INT_MAX))
		return (0);
	return (1);
}

int	run_builts(t_command *cmd)
{
	if (!ft_strncmp(cmd->argumants[0], "echo", INT_MAX))
		return (ft_echo(cmd->argumants));
	else if (!ft_strncmp(cmd->argumants[0], "pwd", INT_MAX))
		return (ft_pwd());
	else if (!ft_strncmp(cmd->argumants[0], "env", INT_MAX))
		return (ft_env(ft_bash()->list, cmd->argumants));
	else if (!ft_strncmp(cmd->argumants[0], "export", INT_MAX))
		return (ft_export(cmd->argumants));
	else if (!ft_strncmp(cmd->argumants[0], "unset", INT_MAX))
		return (ft_unset(cmd->argumants, &ft_bash()->list));
	else if (!ft_strncmp(cmd->argumants[0], "exit", INT_MAX))
		return (ft_exit(cmd->argumants));
	else if (!ft_strncmp(cmd->argumants[0], "cd", INT_MAX))
		return (ft_cd(cmd->argumants));
	return (1);
}

void	child_builtin_helper(t_command *cmd, int input, int *pipe)
{
	int	status;

	if (check_if_builts(cmd->argumants[0]) == 0)
	{
		if (input != 0)
			ft_dup(input, STDIN_FILENO);
		if (pipe != NULL)
		{
			close(pipe[0]);
			ft_dup(pipe[1], STDOUT_FILENO);
		}
		redirect_file(cmd);
		status = run_builts(cmd);
		clean_exit(status);
	}
}

int	builtin_helper(t_command *cmd)
{
	int	status;

	save_stdfd();
	set_under_score(cmd->argumants);
	status = redirect_builtin(cmd);
	if (status != 0)
		return (revert_stdfd(), status);
	status = run_builts(cmd);
	return (revert_stdfd(), status);
}
