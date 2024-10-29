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
	ft_bash()->env = envp;
}

// int main(int argc, char **argv, char **envp)
// {
// 	int status;


// 	t_command cmd;
// 	cmd.argumants = malloc(sizeof(char *) * 2);
// 	cmd.argumants[0] = ft_strdup("ls");
// 	cmd.argumants[1] = NULL;
// 	cmd.files = malloc(sizeof(t_files));
// 	cmd.files->name = ft_strdup("gg.txt");
// 	cmd.files->redirec = ft_strdup("redout");
// 	cmd.files->next =  NULL;
// 	cmd.next = NULL;
// 	argc += 1;
// 	ft_strlen(argv[0]);
// 	init_global_data(envp);
// 	status = excution(&cmd);
// 	return (status);
// }
