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
		//TODO
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

void	set_as_command(t_command *command, char *arg)
{
	int		i;
	char	**tmp;
	int		new_len;

	i = 0;
	if (command->args == NULL)
	{
		command->args = (char **)my_malloc(sizeof(char *) * 2);
		{
			command->args[0] = ft_strdup(arg);
			command->args[1] = NULL;
		}
	}
	else
	{
		while (command->args[i])
			i++;
		new_len = i + 2;
		tmp = (char **)my_malloc(sizeof(char *) * new_len);
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
}

void	add_another_one(t_command **command)
{
	t_command *new_node;

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
		if ((!ft_strncmp(tokens->tokenType, "command", ft_strlen("command")))
		|| (!ft_strncmp(tokens->tokenType, "argurment", ft_strlen("argurment"))))
			set_as_command(command, tokens->token);
		else if (!ft_strncmp(tokens->tokenType, "pipe", ft_strlen("pipe")))
			add_another_one(&command);
		else if((!ft_strncmp(tokens->tokenType, "input", ft_strlen("input")))
			|| (!ft_strncmp(tokens->tokenType, "output", ft_strlen("output"))) ||
			(!ft_strncmp(tokens->tokenType, "appaned", ft_strlen("appaned")))
			|| (!ft_strncmp(tokens->tokenType, "herdoc", ft_strlen("herdoc"))))
			handle_rediration(command, &tokens);
		tokens = tokens->next;
	}
	return (command_list);
}
