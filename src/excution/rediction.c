/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:12:20 by echoubby          #+#    #+#             */
/*   Updated: 2024/12/02 14:20:01 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_ambiguous_child(char *filename, int flag)
{
	int		var;

	var = 0;
	if (filename[0] == '$')
		var = 1;
	if (flag == 1)
		return (filename);
	else if (flag == 2)
	{
		if (expand_name(filename) != NULL)
			return (expand_name(filename));
		return (ft_strdup(""));
	}
	else if (flag == 0)
	{
		ambigous_helper(filename, var);
		return (expand_name(filename));
	}
	return (filename);
}

int	check_file_b_child(char *filename, int mode, int flag)
{
	filename = check_ambiguous_child(filename, flag);
	if (mode == 1)
	{
		if (is_a_directory(filename, 0))
			return (1);
		if (access(filename, F_OK) != -1 && access(filename, W_OK) == -1)
		{
			err_n_ex(NULL, NULL, filename, 1);
			return (1);
		}
		return (0);
	}
	if (access(filename, R_OK) == -1)
	{
		err_n_ex(NULL, NULL, filename, 1);
		return (1);
	}
	return (0);
}

int	redirect_in_file_b_child(char *filename, int flag)
{
	int	fd;

	fd = -1;
	if (check_file_b_child(filename, 0, flag))
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		err_n_ex("No such file or directory", NULL, filename, 1);
	ft_dup(fd, STDIN_FILENO);
	return (0);
}

int	redirect_out_b_child(char *filename, int append, int flag)
{
	int	fd;

	if (check_file_b_child(filename, 1, flag) == 0)
	{
		if (filename[0] == '$' && (flag == 0 || flag == 2))
			filename = expand_name(filename);
		if (filename == NULL)
			filename = ft_strdup("");
		if (append == 1)
			fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			err_n_ex("No such file or directory", NULL, filename, 1);
		ft_dup(fd, STDOUT_FILENO);
	}
	else
		return (1);
	return (0);
}

int	redirect_file(t_command *cmd)
{
	while (cmd->files != NULL)
	{
		if (!ft_strncmp(cmd->files->redirec, "<<", INT_MAX))
			ft_dup(cmd->files->fd[0], STDIN_FILENO);
		if (!ft_strncmp(cmd->files->redirec, "<", INT_MAX))
			if (redirect_in_file_b_child(cmd->files->name, cmd->files->flag))
				return (1);
		if (!ft_strncmp(cmd->files->redirec, ">", INT_MAX))
			if (redirect_out_b_child(cmd->files->name, 0, cmd->files->flag))
				return (1);
		if (!ft_strncmp(cmd->files->redirec, ">>", INT_MAX))
			if (redirect_out_b_child(cmd->files->name, 1, cmd->files->flag))
				return (1);
		cmd->files = cmd->files->next;
	}
	return (0);
}
