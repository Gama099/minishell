#include "../includes/minishell.h"

t_bash	*ft_bash(void)
{
	static t_bash	shell;

	return (&shell);
}

void	init_global_data(char **envp)
{
	ft_bash()->fd_stdin = dup(STDIN_FILENO);
	ft_bash()->fd_stdout= dup(STDOUT_FILENO);
	ft_bash()->list = env_to_list(envp);
}
