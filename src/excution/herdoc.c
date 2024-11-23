#include "../../includes/minishell.h"

char	*buffer_glue(char **buffer, char **input, t_files *files)
{
	char	*tmp;
	char	*new_buffer;

	if (files->flag == 0 && to_expand(*input)) //delimi is var and no quotes mean expand
		new_buffer = ft_strjoin(*buffer, expand_name(*input));
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
				i++;
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
	close(files->fd[0]);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, sigint_handler_hd);
	input = readline(">");
	while (strcmp(files->name, input) != 0) //change strcmp later
	{
		buffer = buffer_glue(&buffer, &input, files);
		input = readline(">");
	}
	write(files->fd[1], buffer, ft_strlen(buffer));
	free(buffer);
	buffer = NULL;
	close(files->fd[1]);
	clean_exit(0);
}

int	herdoc_helper(t_files	*files)
{
	int		pid;
	int		status;

	status = 0;
	if (pipe(files->fd) == -1)
		err_n_exit("syscall failed", "pipe", NULL, 1);
	pid = ft_fork();
	if (pid == 0)
		run_herdoc_child(files);
	waitpid(pid, &status, 0);
	close(files->fd[1]);
	return ((((status) & 0xff00) >> 8));
}

int	ft_herdoc(t_command	*cmd)
{
	t_files		*file;
	int			status;
	int			i;
	t_command	*tmp;

	tmp = cmd;
	i = red_counter(cmd);
	if (i > 16)
		return (err_msg("maximum here-document count exceeded", NULL, NULL), 1);
	else if (i == 0)
		return (0);
	while (cmd != NULL)
	{
		file = cmd->files;
		while (cmd->files != NULL)
		{
			if (!ft_strncmp(cmd->files->redirec, "<<", INT_MAX))
				status = herdoc_helper(cmd->files);
			cmd->files = cmd->files->next;
		}
		cmd->files = file;
		cmd = cmd->next;
	}
	cmd = tmp;
	return (status);
}
