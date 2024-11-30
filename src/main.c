/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:16:47 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:16:49 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_global_data(char **envp)
{
	ft_bash()->exit_status = 0;
	if (!envp[0])
		ft_env_i();
	else
		ft_bash()->list = env_to_list(envp);
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
	t_tokens	*tokens;

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
	}
	return (status);
}
