/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hadd <sel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:47:46 by sel-hadd          #+#    #+#             */
/*   Updated: 2024/11/29 22:49:12 by sel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_argument_to_command(t_command *command, char *arg)
{
	int		i;
	char	**tmp;
	int		new_len;

	i = 0;
	while (command->args[i])
		i++;
	new_len = i + 2;
	tmp = (char **)my_malloc(sizeof(char *) * new_len);
	if (tmp == NULL)
		return ;
	i = 0;
	while (command->args[i])
	{
		tmp[i] = ft_strdup(command->args[i]);
		i++;
	}
	tmp[i++] = ft_strdup(arg);
	tmp[i] = NULL;
	command->args = tmp;
}

void	set_as_command(t_command *command, char *arg)
{
	if (command->args == NULL)
		initialize_argumants(command, arg);
	else
		add_argument_to_command(command, arg);
}

void	add_another_one(t_command **command)
{
	t_command	*new_node;

	new_node = init_cmd_node();
	(*command)->next = new_node;
	*command = (*command)->next;
}

t_command	*to_strcuct(t_tokens *tokens)
{
	t_command	*command;
	t_command	*command_list;

	command = init_cmd_node();
	command_list = command;
	while (tokens)
	{
		if ((!ft_strcmps(tokens->tokentype, "command"))
			|| (!ft_strcmps(tokens->tokentype, "argurment")))
			set_as_command(command, tokens->token);
		else if (!ft_strcmps(tokens->tokentype, "pipe"))
			add_another_one(&command);
		else if ((!ft_strcmps(tokens->tokentype, "input"))
			|| (!ft_strcmps(tokens->tokentype, "output"))
			|| (!ft_strcmps(tokens->tokentype, "appaned"))
			|| (!ft_strcmps(tokens->tokentype, "herdoc")))
			handle_rediration(command, &tokens);
		tokens = tokens->next;
	}
	return (command_list);
}
