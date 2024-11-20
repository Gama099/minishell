#include "../../includes/minishell.h"

int	is_a_directory(char *filename, int bltn)
{
	struct stat	buff;

	ft_bzero(&buff, sizeof(buff));
	stat(filename, &buff);
	if ((buff.st_mode & __S_IFMT) == __S_IFDIR)
	{
		err_msg("Is a directory", NULL, filename);
		if (bltn == 0)
			clean_exit(1);
		return (1);
	}
	return (0);
}

int	check_ambiguous(char **filename, int flag)
{
	char	*ex_str;

	if (*filename[0] == '$')
	{
		if (flag == 1)//in single quote no ambiguos no expand
			return (0);
		else if (flag == 2)//in double quote no ambiguos just expand
		{
			if (expand_word(*filename) != NULL)
			{
				*filename = expand_word(*filename);
				return (0);
			}
		}
		else if (flag == 0)//in no quotes no expand if var not exists just ambiguos//in no quotes no ambiguos just expand if var exists
		{
			ex_str = expand_word(*filename);
			if (ex_str == NULL || ft_strchrr(ex_str, ' ') != -1)// ither var contain space or var is not in env
				return (err_msg("ambiguous redirection", NULL, *filename), 1);
			if (ex_str != NULL)
				*filename = ex_str;//work in all
		}
	}
	return (0);
}

int	redirect_no_cmd(t_files	*files)
{
	while (files != NULL)
	{
		if (!ft_strncmp(files->redirec, "<<", INT_MAX))
			ft_dup(files->fd[0], STDIN_FILENO);
		if (!ft_strncmp(files->redirec, "<", INT_MAX))
			if (redirect_in_file_b_child(files->name, files->flag))
				return (1);
		if (!ft_strncmp(files->redirec, ">", INT_MAX))
			if (redirect_out_b_child(files->name, 0, files->flag))
				return (1);
		if (!ft_strncmp(files->redirec, ">>", INT_MAX))
			if (redirect_out_b_child(files->name, 1, files->flag))
				return (1);
		files = files->next;
	}
	return (0);
}
