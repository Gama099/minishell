#include "../../includes/minishell.h"

t_bash	*ft_bash(void)
{
	static t_bash	shell;

	return (&shell);
}

void   init_global_data(char **envp)
{
	ft_bash()->exit_status = 0;
	if (!envp[0])
		ft_env_i();
	else
		ft_bash()->list = env_to_list(envp);
}

void	init_status(int status)
{
	ft_bash()->exit_status = status;
}

char	*prompt(void)
{
	char	*input;

	input = readline("minishell$> ");
	if (input == NULL)
	{
		free_env(ft_bash()->list);
		write(1, "exit\n", 5);
		exit(ft_bash()->exit_status);
	}
	if (*input)
		add_history(input);
	return (ft_strdup(input));
}
void print_files(t_files *files)
{
    while (files) {
        printf("    File:\n");
        printf("      Name: %s\n", files->name ? files->name : "NULL");
        printf("      Redirection: %s\n", files->redirec ? files->redirec : "NULL");
        printf("      FD: [%d, %d]\n", files->fd[0], files->fd[1]);
        files = files->next;
    }
}

void print_command(t_command *cmd)
{
    int i = 0;
    while (cmd) {
        printf("Command %d:\n", ++i);
        printf("  Arguments:\n");
        if (cmd->args) {
            for (int j = 0; cmd->args[j]; j++) {
                printf("    [%d]: %s\n", j, cmd->args[j]);
            }
        } else {
            printf("    NULL\n");
        }

        printf("  Files:\n");
        if (cmd->files->name || cmd->files->redirec) {
            print_files(cmd->files);
        } else {
            printf("    None\n");
        }

        cmd = cmd->next;
        if (cmd) {
            printf("  |\n  v\n");
        }
    }
}

// void	free_struct(t_command *cmd)
// {

// }

int main(int ac, char **av, char **envp)
{
    t_tokens    *tokens;
    char        *buffer;
	t_command	*cmd;
	int			status;

	(void)ac;
	(void)av;
	init_global_data(envp);
    while (1)
    {
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sigint_handler_main);
		buffer = prompt();
		tokens = getTokens(buffer);
		expand_varibles(&tokens);
		join_token_syblings(&tokens);
		parser(&tokens);
		tokenaze_var(&tokens);
		status = handle_syntax_errors(tokens);
		if (status == 0)
		{
			cmd = to_strcuct(tokens);
			status = ft_herdoc(cmd);
			if (status == 0)
				init_status(excution(cmd));
			else
				init_status(status);
		}
		else
			init_status(status);
		//free_struct(cmd);
    }
		return (0);
}

	// printf("cmd = %s\n", cmd->argumants[0]);
		// printf("cmd = %s\n", cmd->argumants[1]);
		// printf("file = %s\n", cmd->files->name);
		// printf("deli = %s\n", cmd->files->redirec);
			//printf("%s", buffer);
			/*for (t_tokens *i = tokens; i; i = i->next)
			{
				printf("%s\n", i->token);
			}*/
			// printf("cmd = %s\n", command->argumants[0]);
			// printf("cmd = %s\n", command->argumants[1]);
			// printf("file = %s\n", command->files->name);
			// printf("red = %s\n", command->files->redirec);
		//print_command(command);
        /*while (tokens)
        {
            printf("\n[%s]\n", tokens->token);
            printf("[%s]\n", tokens->tokenType);
			printf("[%d]\n", tokens->sing_qoute);
            tokens = tokens->next;
        }*/
		//my_free();
		//init_struct();

