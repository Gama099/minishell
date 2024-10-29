#include "../includes/minishell.h"

void	 	ft_dup(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		pr_err_msg("syscall failed", "dup2", NULL);
	else
	{
		if (close(old_fd) == -1)
			pr_err_msg("syscall failed", "close", NULL);
	}
}
