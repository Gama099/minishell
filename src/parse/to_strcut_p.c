/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_strcut_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hadd <sel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:47:46 by sel-hadd          #+#    #+#             */
/*   Updated: 2024/11/29 22:49:00 by sel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*init_cmd_node(void)
{
	t_command	*command;

	command = (t_command *)my_malloc(sizeof(t_command));
	command->args = NULL;
	command->next = NULL;
	command->files = (t_files *)my_malloc(sizeof(t_files));
	command->files->name = NULL;
	command->files->next = NULL;
	command->files->flag = 0;
	command->files->redirec = NULL;
	return (command);
}

void	handle_rediration(t_command *command, t_tokens **tokens)
{
	t_files	*current;
	t_files	*new_file;

	current = command->files;
	if (command->files->name != NULL)
	{
		new_file = (t_files *)my_malloc(sizeof(t_files));
		if (new_file == NULL)
			return ;
		new_file->flag = 0;
		while (current->next)
			current = current->next;
		current->next = new_file;
		current = new_file;
		new_file->next = NULL;
	}
	current->redirec = ft_strdup((*tokens)->token);
	(*tokens) = (*tokens)->next;
	if (*tokens)
		current->name = ft_strdup((*tokens)->token);
	if ((*tokens)->qoute_type)
		command->files->flag = (*tokens)->qoute_type;
}

void	initialize_argumants(t_command *command, char *arg)
{
	command->args = (char **)my_malloc(sizeof(char *) * 2);
	if (command->args == NULL)
		return ;
	command->args[0] = ft_strdup(arg);
	command->args[1] = NULL;
}
