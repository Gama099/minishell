/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:12:29 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:12:31 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1] != '\0')
			return (EXIT_SUCCESS);
		else if (str[i] == '=' && str[i + 1] == '\0')
			return (2);
		i++;
	}
	return (EXIT_FAILURE);
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
	if (!ft_strncmp(cmd->args[0], "echo", INT_MAX))
		return (ft_echo(cmd->args));
	else if (!ft_strncmp(cmd->args[0], "pwd", INT_MAX))
		return (ft_pwd());
	else if (!ft_strncmp(cmd->args[0], "env", INT_MAX))
		return (ft_env(ft_bash()->list, cmd->args));
	else if (!ft_strncmp(cmd->args[0], "export", INT_MAX))
		return (ft_export(cmd->args));
	else if (!ft_strncmp(cmd->args[0], "unset", INT_MAX))
		return (ft_unset(cmd->args, &ft_bash()->list));
	else if (!ft_strncmp(cmd->args[0], "exit", INT_MAX))
		return (ft_exit(cmd->args));
	else if (!ft_strncmp(cmd->args[0], "cd", INT_MAX))
		return (ft_cd(cmd->args));
	return (1);
}

void	child_builtin_helper(t_command *cmd, int input, int *pipe)
{
	int	status;

	if (check_if_builts(cmd->args[0]) == 0)
	{
		if (input != 0)
			ft_dup(input, STDIN_FILENO);
		if (pipe != NULL)
		{
			ft_close(pipe[0]);
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
	set_under_score(cmd->args);
	status = redirect_builtin(cmd);
	if (status != 0)
		return (revert_stdfd(), status);
	status = run_builts(cmd);
	return (revert_stdfd(), status);
}
