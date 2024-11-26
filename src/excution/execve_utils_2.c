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
