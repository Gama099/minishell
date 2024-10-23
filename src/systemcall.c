#include "minishell.h"

void	 	ft_dup(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		printf("syscall failed dup2\n");
	else
	{
		if (close(old_fd) == -1)
			printf("syscall failed close\n");
	}
}
