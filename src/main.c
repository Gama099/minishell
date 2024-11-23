#include "../includes/minishell.h"

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
		free_struct(cmd);
    }
		return (0);
}


