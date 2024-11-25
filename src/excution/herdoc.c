#include "../../includes/minishell.h"

char	*buffer_glue(char **buffer, char **input, t_files *files)
{
	char	*tmp;
	char	*new_buffer;

	if (files->flag == 0 && to_expand(*input)) //delimi is var and no quotes mean expand
	{
		tmp = expand_name(*input);
		new_buffer = ft_strjoin(*buffer, tmp);
		free(tmp);
	}
	else
		new_buffer = ft_strjoin(*buffer, *input);
	tmp = new_buffer;
	new_buffer = ft_strjoin(tmp, "\n");
	free(tmp);
	free(*buffer);
	free(*input);
	tmp = NULL;
	return (new_buffer);
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
					err_n_exit("syscall failed", "pipe", NULL, 1);
				i++;
			}
			cmd->files = cmd->files->next;
		}
		cmd->files = file;
		cmd = cmd->next;
	}
	return (i);
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
	while (ft_strcmp(files->name, input) != 0) //change strcmp later
	{
		buffer = buffer_glue(&buffer, &input, files);
		input = readline(">");
		if (input == NULL)
			break;
	}
	write(files->fd[1], buffer, ft_strlen(buffer));
	free(buffer);
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
					run_herdoc_child(cmd->files );
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
		return (err_msg("maximum here-document count exceeded", NULL, NULL), 1);
	}
	else if (i == 0)
		return (0);
	status = herdoc_helper(cmd);
	cmd = tmp;
	close_pipes(cmd);
	return (status);
}
