#include "../includes/minishell.h"

void	ft_dup(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		err_msg("syscall failed", "dup2", NULL);
	else
	{
		if (close(old_fd) == -1)
			err_msg("syscall failed", "close", NULL);
	}
}

void	save_stdfd(void)
{
	ft_bash()->fd_stdin = dup(STDIN_FILENO);
	if (ft_bash()->fd_stdin == -1)
		err_msg("syscall failed", "dup", NULL);
	ft_bash()->fd_stdout = dup(STDOUT_FILENO);
	if (ft_bash()->fd_stdout == -1)
		err_msg("syscall failed", "dup", NULL);
}

void	revert_stdfd(void)
{
	ft_dup(ft_bash()->fd_stdin, STDIN_FILENO);
	ft_dup(ft_bash()->fd_stdout, STDOUT_FILENO);
}
