/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:12:13 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:12:15 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*buffer_glue(char **buffer, char **input, int flag)
{
	char	*tmp;
	char	*new_buffer;
	char	*str;

	str = ft_strrchr(*input, '$');
	if (str != NULL && flag == 0)
	{
		tmp = expand_herdoc(*input);
		if (tmp == NULL)
			new_buffer = ft_strjoin(*buffer, *input);
		else
			new_buffer = ft_strjoin(*buffer, tmp);
	}
	else
		new_buffer = ft_strjoin(*buffer, *input);
	tmp = new_buffer;
	new_buffer = ft_strjoin(tmp, "\n");
	tmp = NULL;
	return (new_buffer);
}

void	run_herdoc_child(t_files *files)
{
	char	*buffer;
	char	*input;

	buffer = ft_strdup("");
	ft_close(files->fd[0]);
	input = readline(">");
	if (input == NULL)
		return ;
	while (ft_strcmp(files->name, input) != 0)
	{
		buffer = buffer_glue(&buffer, &input, files->flag);
		input = readline(">");
		if (input == NULL)
			break ;
	}
	write(files->fd[1], buffer, ft_strlen(buffer));
	buffer = NULL;
	ft_close(files->fd[1]);
}

int	herdoc_helper(t_command	*cmd)
{
	int		pid;
	int		status;
	t_files	*file;

	status = 0;
	pid = ft_fork();
	if (pid == 0)
	{
		signal(SIGINT, sigint_handler_hd);
		while (cmd != NULL)
		{
			file = cmd->files;
			while (cmd->files != NULL)
			{
				if (!ft_strncmp(cmd->files->redirec, "<<", INT_MAX))
					run_herdoc_child(cmd->files);
				cmd->files = cmd->files->next;
			}
			cmd->files = file;
			cmd = cmd->next;
		}
		clean_exit(0);
	}
	waitpid(pid, &status, 0);
	return ((((status) & 0xff00) >> 8));
}

void	close_pipes(t_command	*cmd)
{
	t_files	*file;

	while (cmd != NULL)
	{
		file = cmd->files;
		while (cmd->files != NULL)
		{
			if (!ft_strncmp(cmd->files->redirec, "<<", INT_MAX))
				ft_close(cmd->files->fd[1]);
			cmd->files = cmd->files->next;
		}
		cmd->files = file;
		cmd = cmd->next;
	}
}

int	ft_herdoc(t_command	*cmd)
{
	int			status;
	int			i;
	t_command	*tmp;

	tmp = cmd;
	i = red_counter(cmd);
	if (i > 16)
	{
		close_pipes(cmd);
		err_n_ex("maximum here-document count exceeded", NULL, NULL, 2);
	}
	else if (i == 0)
		return (0);
	signal(SIGINT, SIG_IGN);
	status = herdoc_helper(cmd);
	cmd = tmp;
	close_pipes(cmd);
	return (status);
}
