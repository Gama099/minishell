/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_builtins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:13:28 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:13:32 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_file_b(char *filename, int mode, int flag)
{
	if (check_ambiguous(&filename, flag) == 1)
		return (1);
	if (mode == 1)
	{
		if (is_a_directory(filename, 1))
			return (1);
		if (access(filename, F_OK) != -1 && access(filename, W_OK) == -1)
		{
			err_msg(NULL, NULL, filename);
			return (1);
		}
		return (0);
	}
	if (access(filename, F_OK | R_OK) == -1)
	{
		err_msg(NULL, NULL, filename);
		return (1);
	}
	return (0);
}

int	redirect_in_file_b(char *name, int flag)
{
	int	fd;

	fd = -1;
	if (check_file_b(name, 0, flag))
		return (1);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (err_msg("No such file or directory", NULL, name), 1);
	ft_dup(fd, STDIN_FILENO);
	return (0);
}

int	redirect_out_b(char *name, int append, int flag)
{
	int	fd;

	if (check_file_b(name, 1, flag) == 0)
	{
		if (name[0] == '$' && (flag == 0 || flag == 2))
			name = expand_name(name);
		if (append == 1)
			fd = open(name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			return (err_msg("No such file or directory", NULL, name), 1);
		ft_dup(fd, STDOUT_FILENO);
	}
	else
		return (1);
	return (0);
}

int	redirect_builtin(t_command *cmd)
{
	while (cmd->files != NULL)
	{
		if (!ft_strncmp(cmd->files->redirec, "<<", INT_MAX))
			ft_dup(cmd->files->fd[0], STDIN_FILENO);
		if (!ft_strncmp(cmd->files->redirec, "<", INT_MAX))
			if (redirect_in_file_b(cmd->files->name, cmd->files->flag) == 1)
				return (1);
		if (!ft_strncmp(cmd->files->redirec, ">", INT_MAX))
			if (redirect_out_b(cmd->files->name, 0, cmd->files->flag) == 1)
				return (1);
		if (!ft_strncmp(cmd->files->redirec, ">>", INT_MAX))
			if (redirect_out_b(cmd->files->name, 1, cmd->files->flag) == 1)
				return (1);
		cmd->files = cmd->files->next;
	}
	return (0);
}
