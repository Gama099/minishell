#include "../includes/minishell.h"

t_memoryblock *head = NULL;

t_bash	*ft_bash(void)
{
	static t_bash	shell;

	return (&shell);
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
		expand_varibles(&tokens);
		join_token_syblings(&tokens);
		parser(&tokens);
		tokenaze_var(&tokens);
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
