#include "minishell.h"

int	check_ambiguous(char *filename)
{
	if ((filename == NULL || ft_strchrr(filename, ' ') != -1))
		return (printf("ambiguous redirection"),1);
	return (0);
}

int	check_file_b(char *filename, int mode)
{
	if (check_ambiguous(filename) == 1)
		return (1);
	if (mode == 1)
	{
		if (is_a_directory(filename, 1))
			return (1);
		if (access(filename, F_OK) != -1 && access(filename, W_OK) == -1)
		{
			perror(filename);
			return (1);
		}
		return (0);
	}
	if (access(filename, F_OK | R_OK) == -1)
	{
		perror(filename);
		return (1);
	}
	return (0);
}

int	redirect_in_file_b(char *filename)
{
	int	fd;

	fd = -1;
	if (check_file_b(filename, 0))
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (printf("No such file or directory"), 1);
	ft_dup(fd, STDIN_FILENO);
	return (0);
}

int	redirect_out_b(char *filename, int append)
{
	int	fd;

	if (check_file_b(filename, 1) == 0)
	{
		if (append == 1)
			fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			return (printf("No such file or directory"),1);
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
		if (!ft_strncmp(cmd->files->redirec, "herdoc", INT_MAX))	
			ft_dup(cmd->files->fd[0], STDIN_FILENO);
		if (!ft_strncmp(cmd->files->redirec, "redin", INT_MAX))
			if (redirect_in_file_b(cmd->files->name))
				return (1);
		if (!ft_strncmp(cmd->files->redirec, "redout", INT_MAX))
			if (redirect_out_b(cmd->files->name, 0))
				return (1);
		if (!ft_strncmp(cmd->files->redirec, "redoapp", INT_MAX))
			if (redirect_out_b(cmd->files->name, 1))
				return (1);
		cmd->files = cmd->files->next;
	}
	return (0);
}