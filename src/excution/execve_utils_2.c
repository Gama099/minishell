/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:12:00 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:12:02 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_access(char *path)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			return (0);
		else
			return (2);
	}
	else
		return (1);
}

int	red_counter(t_command	*cmd)
{
	t_files	*file;
	int		i;

	i = 0;
	while (cmd != NULL)
	{
		file = cmd->files;
		while (cmd->files != NULL)
		{
			if (!ft_strncmp(cmd->files->redirec, "<<", INT_MAX))
			{
				if (pipe(cmd->files->fd) == -1)
					err_n_ex("syscall failed", "pipe", NULL, 1);
				i++;
			}
			cmd->files = cmd->files->next;
		}
		cmd->files = file;
		cmd = cmd->next;
	}
	return (i);
}

char	**split_env(void)
{
	char	**splited_path;
	char	*tmp;

	tmp = get_path();
	if (tmp == NULL)
		splited_path = ft_split("./:", ':');
	else
		splited_path = ft_split(tmp, ':');
	return (splited_path);
}

int	excution_parse(t_command *cmd)
{
	if (cmd->args == NULL && cmd->files->name == NULL)
		return (1);
	else if (cmd->args != NULL && spaces(cmd) == 1)
		return (1);
	return (0);
}

int	excution_status(int status)
{
	if (status == 131)
		return (status);
	if (((status) & 0x7f) == 2)
		return (130);
	return ((((status) & 0xff00) >> 8));
}
