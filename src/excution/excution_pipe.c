/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:11:52 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:11:54 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	counter(void *count, int mode)
{
	int			i;
	t_command	*cmd;

	i = 0;
	if (mode == 1)
	{
		cmd = (t_command *)count;
		while (cmd->next != NULL)
		{
			cmd = cmd->next;
			i++;
		}
	}
	return (i);
}

int	ft_wait(t_pipes	*var)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (i <= var->j)
		waitpid(var->pid[i++], &status, 0);
	return (status);
}

int	pipe_helper(int input, t_command *cmd, int *pipe)
{
	int	pid;

	if (cmd->args == NULL)
		pid = no_cmd(cmd);
	else if (cmd->next == NULL)
		pid = one_cmd(cmd, input, NULL);
	else
		pid = one_cmd(cmd, input, pipe);
	if (input != 0)
		ft_close(input);
	return (pid);
}

t_pipes	*pipe_call(t_command *cmd)
{
	t_pipes	*var;

	var = (t_pipes *)my_malloc(sizeof(t_pipes));
	var->j = counter(cmd, 1);
	var->pid = (int *)my_malloc(sizeof(int) * (var->j + 1));
	return (var);
}

int	excution_pipe(t_command *cmd)
{
	int		fd[2];
	int		old_input;
	int		i;
	t_pipes	*var;

	i = 0;
	old_input = 0;
	var = pipe_call(cmd);
	while (cmd != NULL)
	{
		if (cmd->next != NULL)
		{
			if (pipe(fd) == -1)
				err_n_ex("syscall failed", "pipe", NULL, 1);
		}
		var->pid[i] = pipe_helper(old_input, cmd, fd);
		if (cmd->next != NULL)
		{
			old_input = fd[0];
			ft_close(fd[1]);
		}
		cmd = cmd->next;
		i++;
	}
	return (ft_wait(var));
}
