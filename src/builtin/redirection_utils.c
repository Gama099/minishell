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

int	ambigous_helper_builtins(char	**file, int is_var)
{
	char	*ex_fi;
	char	**spl_ex_fi;

	spl_ex_fi = NULL;
	ex_fi = expand_name(*file);
	if (ex_fi != NULL)
	{
		spl_ex_fi = ft_split(ex_fi, ' ');
		if (is_var && (spl_ex_fi[0] != NULL && spl_ex_fi[1] != NULL)) // if both != NULL that mean there was space
		{
			free(ex_fi);
			free_ary(spl_ex_fi);
			return (err_msg("ambiguous redirection", NULL, *file), 1);
		}
	}
	else if (is_var && ex_fi == NULL && ft_strlen(*file) > 1) // if both != NULL that mean there was space
		return (free(ex_fi), err_msg("ambiguous redirection", NULL, *file), 1);
	if (spl_ex_fi != NULL)
	{
		*file = ft_strdup(spl_ex_fi[0]);
		return (free_ary(spl_ex_fi), 0);
	}
	return (0);
}

int	check_ambiguous(char **filename, int flag)
{
	int		var;

	var = 0;
	if (*filename[0] == '$')
		var = 1;
	if (flag == 1) //in single quote no ambiguos no expand
		return (0);
	else if (flag == 2) //in double quote no ambiguos just expand
	{
		if (expand_name(*filename) != NULL)
		{
			*filename = expand_name(*filename);
			return (0);
		}
	}
	else if (flag == 0) //in no quotes no expand if var not exists just ambiguos//in no quotes no ambiguos just expand if var exists
	{
		if (ambigous_helper_builtins(filename, var) == 1)
			return (1);
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