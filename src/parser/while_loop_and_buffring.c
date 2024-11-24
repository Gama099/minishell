#include "../../includes/minishell.h"


/*int check_syntax(const char *input) {
    int quote_count = 0;
    char last_char = '\0';

    while (*input) {
        // Check for quotes
        if (*input == '\'' || *input == '\"') {
            quote_count++;
        }

        // Check for consecutive meta-characters
        if (is_meta(*input) && is_meta(last_char)) {
            printf("Syntax error: Consecutive meta-characters detected.\n");
            return 0;
        }

        // Check for redirection errors
        if (is_meta(*input) && (last_char == '\0' || lat_char == ' ')) {
            printf("Syntax error: Redirection operator used incorrectly.\n");
            return 0;
        }

        // Update last character
        last_char = *input;
        input++;
    }

    // Check for unmatched quotes
    if (quote_count % 2 != 0) {
        printf("Syntax error: Unmatched quotes detected.\n");
        return 0;
    }

    return 1; // No syntax errors found
}
*/

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
        if (cmd->argumants) {
            for (int j = 0; cmd->argumants[j]; j++) {
                printf("    [%d]: %s\n", j, cmd->argumants[j]);
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


t_bash	*ft_bash(void)
{
	static t_bash	shell;

	return (&shell);
}

void   init_global_data(char **envp)
{
	ft_bash()->fd_stdin = dup(STDIN_FILENO);
	ft_bash()->fd_stdout= dup(STDOUT_FILENO);
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

int main(int ac, char **av, char **envp)
{
    char        *input;
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
		printf("\033[1;35m");
		printf("╔════════════════════════════════════════╗\n");
		printf("║ \033[1;36mWelcome to the best C World! \033[1;35m║\n");
		printf("║ \033[0;32mWhere Coding Meets Fun \033[1;35m║\n");
		printf("╚════════════════════════════════════════╝\n");
		printf("\033[1;33mStay Awesome, Keep Coding!\033[0m\n");
        input = readline("minishell$> ");
        if(input == NULL)
			clean_exit(ft_bash()->exit_status);
		if (!ft_strncmp(input, "exit", ft_strlen(input)))
			clean_exit(ft_bash()->exit_status);
		/*if (!check_syntax(input))
		{
			free (input);
			write(1, "\n", 1);
		}*/
		buffer = ft_strdup(input);
		add_history(input);
		tokens = getTokens(buffer);

		 printf("tokenaziatoin:\n");
		 for (t_tokens *i = tokens; i; i = i->next)
             {
		 		printf("\t\ttoken [%s]\n", i->token);
		 		printf("\t\t expnad [%d]\n", i->expand_env);
		 		printf("\t\t  join[%d]\n", i->join_with_next);
		 		printf("\t\t   qoute[%d]\n", i->qoute_type);
		 		printf("\t\t    type[%s]\n", i->tokenType);
		 	}

		expand_varibles(&tokens);

		 printf("expand:\n");
		  for (t_tokens *i = tokens; i; i = i->next)
             {
		 		printf("\t\ttoken [%s]\n", i->token);
		 		printf("\t\t expnad [%d]\n", i->expand_env);
		 		printf("\t\t  join[%d]\n", i->join_with_next);
		 		printf("\t\t   qoute[%d]\n", i->qoute_type);
		 		printf("\t\t    type[%s]\n", i->tokenType);
		 	}

		join_token_syblings(&tokens);

		printf("joining:\n");
		 for (t_tokens *i = tokens; i; i = i->next)
             {
		 		printf("\t\ttoken [%s]\n", i->token);
		 		printf("\t\t expnad [%d]\n", i->expand_env);
		 		printf("\t\t  join[%d]\n", i->join_with_next);
		 		printf("\t\t   qoute[%d]\n", i->qoute_type);
		 		printf("\t\t    type[%s]\n", i->tokenType);
		 	}

		parser(&tokens);

		printf("parsing:\n");
		 for (t_tokens *i = tokens; i; i = i->next)
             {
		 		printf("\t\ttoken [%s]\n", i->token);
		 		printf("\t\t expnad [%d]\n", i->expand_env);
		 		printf("\t\t  join[%d]\n", i->join_with_next);
		 		printf("\t\t   qoute[%d]\n", i->qoute_type);
		 		printf("\t\t    type[%s]\n", i->tokenType);
		 	}
		//sleep(10);

		printf("befooooooore:\n");
		 for (t_tokens *i = tokens; i; i = i->next)
             {
		 		printf("\t\ttoken [%s]\n", i->token);
		 		printf("\t\t expnad [%d]\n", i->expand_env);
		 		printf("\t\t  join[%d]\n", i->join_with_next);
		 		printf("\t\t   qoute[%d]\n", i->qoute_type);
		 		printf("\t\t    type[%s]\n", i->tokenType);
		 	}

		tokenaze_var(&tokens);

		printf("aaaaaaaaaaaaaafter:\n");
		 for (t_tokens *i = tokens; i; i = i->next)
             {
		 		printf("\t\ttoken [%s]\n", i->token);
		 		printf("\t\t expnad [%d]\n", i->expand_env);
		 		printf("\t\t  join[%d]\n", i->join_with_next);
		 		printf("\t\t   qoute[%d]\n", i->qoute_type);
		 		printf("\t\t    type[%s]\n", i->tokenType);
		 	}

			status = (handle_syntax_errors(tokens));
			if (status == 0)
			{
				cmd = to_strcuct(tokens);
				print_command(cmd);
				//sleep(10);
				status = ft_herdoc(cmd);
				if (status == 0)
					init_status(excution(cmd));
				else
					init_status(status);
			}
			else
					init_status(status);
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
        /*while (tokens)
        {
            printf("\n[%s]\n", tokens->token);
            printf("[%s]\n", tokens->tokenType);
			printf("[%d]\n", tokens->sing_qoute);
            tokens = tokens->next;
        }*/
		//my_free();
		//init_struct();
		return (0);
}

