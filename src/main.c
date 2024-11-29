#include "../includes/minishell.h"

t_memoryblock *head = NULL;

t_bash	*ft_bash(void)
{
	static t_bash	shell;

	return (&shell);
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

void	init_global_data(char **envp)
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
		cleanup();
		write(1, "exit\n", 5);
		exit(ft_bash()->exit_status);
	}
	if (*input)
		add_history(input);
	return (ft_strdup(input));
}

t_command	*parsing_process(void)
{
	char		*buffer;
	int			status;
	t_tokens	*tokens;
	t_command	*cmd;

	status = 0;
	buffer = prompt();
	if (is_qoute_valid(buffer) == 0)
	{
		tokens = get_tokens(buffer, 0);
		printf("tokenaziatoin:\n");
		 for (t_tokens *i = tokens; i; i = i->next)
             {
				printf("\t\tadress print = %p\n", i);
		 		printf("\t\ttoken [%s]\n", i->token);
		 		printf("\t\t expnad [%d]\n", i->expand_env);
		 		printf("\t\t  join[%d]\n", i->join_with_next);
		 		printf("\t\t   qoute[%d]\n", i->qoute_type);
		 		printf("\t\t    type[%s]\n", i->tokentype);
		 	}
		expand_varibles(&tokens);
		printf("expand:\n");
		  for (t_tokens *i = tokens; i; i = i->next)
             {
				printf("\t\tadress print = %p\n", i);
		 		printf("\t\ttoken [%s]\n", i->token);
		 		printf("\t\t expnad [%d]\n", i->expand_env);
		 		printf("\t\t  join[%d]\n", i->join_with_next);
		 		printf("\t\t   qoute[%d]\n", i->qoute_type);
		 		printf("\t\t    type[%s]\n", i->tokentype);
		 	}
		join_token_syblings(&tokens);
		printf("joining:\n");
		 for (t_tokens *i = tokens; i; i = i->next)
             {
				printf("\t\tadress print = %p\n", i);
		 		printf("\t\ttoken [%s]\n", i->token);
		 		printf("\t\t expnad [%d]\n", i->expand_env);
		 		printf("\t\t  join[%d]\n", i->join_with_next);
		 		printf("\t\t   qoute[%d]\n", i->qoute_type);
		 		printf("\t\t    type[%s]\n", i->tokentype);
		 	}
		parser(&tokens);
		printf("parsing:\n");
		 for (t_tokens *i = tokens; i; i = i->next)
             {
				printf("\t\tadress print = %p\n", i);
		 		printf("\t\ttoken [%s]\n", i->token);
		 		printf("\t\t expnad [%d]\n", i->expand_env);
		 		printf("\t\t  join[%d]\n", i->join_with_next);
		 		printf("\t\t   qoute[%d]\n", i->qoute_type);
		 		printf("\t\t    type[%s]\n", i->tokentype);
		 	}
			printf("befooooooore:\n");
		 for (t_tokens *i = tokens; i; i = i->next)
             {
				printf("\t\tadress print = %p\n", i);
		 		printf("\t\ttoken [%s]\n", i->token);
		 		printf("\t\t expnad [%d]\n", i->expand_env);
		 		printf("\t\t  join[%d]\n", i->join_with_next);
		 		printf("\t\t   qoute[%d]\n", i->qoute_type);
		 		printf("\t\t    type[%s]\n", i->tokentype);
		 	}
		tokenaze_var(&tokens);
		printf("aaaaaaaaaaaaaafter:\n");
		 for (t_tokens *i = tokens; i; i = i->next)
             {
				printf("\t\tadress print = %p\n", i);
		 		printf("\t\ttoken [%s]\n", i->token);
		 		printf("\t\t expnad [%d]\n", i->expand_env);
		 		printf("\t\t  join[%d]\n", i->join_with_next);
		 		printf("\t\t   qoute[%d]\n", i->qoute_type);
		 		printf("\t\t    type[%s]\n", i->tokentype);
		 	}
		if (handle_syntax_errors(tokens) == 0)
			return (to_strcuct(tokens));
		else
			init_status(2);
	}
	else
		init_status(1);
	return (NULL);
}

int	main(int ac, char **av, char **envp)
{
	t_command	*cmd;
	int			status;

	(void)ac;
	(void)av;
	init_global_data(envp);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sigint_handler_main);
		cmd = parsing_process();
		if (cmd != NULL)
        {
			print_command(cmd);
            status = ft_herdoc(cmd);
            if (status == 0)
                init_status(excution(cmd));
            else
                init_status(status);
        }
		dprintf(2, "exit status = %d\n", ft_bash()->exit_status);
	}
	return (status);
}
