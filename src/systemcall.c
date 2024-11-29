#include "../includes/minishell.h"

void	ft_dup(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		err_msg("syscall failed", "dup2", NULL);
	else
		ft_close(old_fd);
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

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		err_n_exit("error with fork", "fork", NULL, 1);
	return (pid);
}

void	ft_close(int fd)
{
	if (close(fd) == -1)
		err_n_exit("syscall failed", "close", NULL, 1);
}
