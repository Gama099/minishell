#include "../includes/minishell.h"

void	err_msg(char *err_mesg, char *err_cmd, char *err_name)
{
	ft_putstr_fd("minishell: ", 2);
	if (err_mesg)
	{
		if (err_cmd)
		{
			ft_putstr_fd(err_cmd, 2);
			ft_putstr_fd(": ", 2);
		}
		if (err_name)
		{
			ft_putstr_fd(err_name, 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putendl_fd(err_mesg, 2);
	}
	else if (!err_mesg && err_name)
		perror(err_name);
	else if (!err_mesg && err_cmd)
		perror(err_cmd);
}

void	clean_exit(int exit_status)
{
	free_env(ft_bash()->list);
	exit(exit_status);
}

void	err_n_exit(char *err_mesg, char *err_cmd, char *err_name, int status)
{
	err_msg(err_mesg, err_cmd, err_name);
	clean_exit(status);
}
