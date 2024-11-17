#include "../../includes/minishell.h"

#include <sys/time.h>


/*void print_files(t_files *files) {
    while (files) {
        printf("    File:\n");
        printf("      Name: %s\n", files->name ? files->name : "NULL");
        printf("      Redirection: %s\n", files->redirec ? files->redirec : "NULL");
        printf("      FD: [%d, %d]\n", files->fd[0], files->fd[1]);
        files = files->next;
    }
}*/

/*void print_command(t_command *cmd) {
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
        if (cmd->files.name || cmd->files.redirec) {
            print_files(&cmd->files);
        } else {
            printf("    None\n");
        }

        cmd = cmd->next;
        if (cmd) {
            printf("  |\n  v\n");
        }
    }
}
*/

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

void print_files(t_files *files) {
    while (files) {
        printf("    File:\n");
        printf("      Name: %s\n", files->name ? files->name : "NULL");
        printf("      Redirection: %s\n", files->redirec ? files->redirec : "NULL");
        printf("      FD: [%d, %d]\n", files->fd[0], files->fd[1]);
        files = files->next;
    }
}

void print_command(t_command *cmd) {
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

int main(int ac, char **av, char **envp)
{
    char        *input;
    t_tokens    *tokens;
    char        *buffer;
	struct timeval	tv;
	struct timeval	end;
	gettimeofday(&tv, NULL);
	tv.tv_sec;

	(void)ac;
	(void)av;
	init_global_data(envp);
    while (1)
    {
        input = readline("minishell$> ");
        if(!input)
        {
            return (printf("erro\n"));
        }
        //if (!ft_strncmp(input, "exit", ft_strlen(input)))
         //   exit(0);
        buffer = ft_strdup(input);
        add_history(input);
        //printf("%s", buffer);
		// step 1 it return a linkedlist of tokens --
        tokens = getTokens(buffer);
        /*for (t_tokens *i = tokens; i; i = i->next)
        {
            printf("%s\n", i->token);
        }*/
	   // step 2
	   	expand_varibles(&tokens);
		// step 3
        join_token_syblings(&tokens);
		// step 4
        parser(&tokens);
		// step 5
		t_command *command = to_strcuct(tokens);
		print_command(command);
		//sleep(15);
        // printf("cmd = %s\n", command->argumants[0]);
        // printf("cmd = %s\n", command->argumants[1]);
        // printf("file = %s\n", command->files->name);
        // printf("red = %s\n", command->files->redirec);
		excution(command);
		//gettimeofday(&end, NULL);
		//printf("time token to is %ld\n", end.tv_sec - tv.tv_sec);
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
		//for (t_env_list *list = ft_bash()->list; list->next; list = list->next)
		//	printf("name = %s\n value = %s\n", list->name, list->value);
    }
}
