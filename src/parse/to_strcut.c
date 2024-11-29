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
		new_file = malloc(sizeof(t_files));
		if (new_file == NULL)
			return ;
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
    command->args = malloc(sizeof(char *) * 2);
    if (command->args == NULL)
        return;
    command->args[0] = ft_strdup(arg);
    command->args[1] = NULL;
}

void add_argument_to_command(t_command *command, char *arg)
{
    int		i;
    char	**tmp;
    int 	new_len;

	i = 0;
    while (command->args[i])
        i++;
    new_len = i + 2;
    tmp = malloc(sizeof(char *) * new_len);
    if (tmp == NULL)
        return;
    i = 0;
    while (command->args[i])
    {
        tmp[i] = ft_strdup(command->args[i]);
        i++;
    }
    tmp[i++] = ft_strdup(arg);
    tmp[i] = NULL;
    i = 0;
    while (command->args[i])
        free(command->args[i++]);
    free(command->args);
    command->args = tmp;
}

void	set_as_command(t_command *command, char *arg)
{
	int		i;
	char	**tmp;
	int		new_len;

	i = 0;
	if (command->args == NULL)
		initialize_argumants(command, arg);
	else
		add_argument_to_command(command, arg);
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
		if ((!ft_strcmps(tokens->tokenType, "command"))
			|| (!ft_strcmps(tokens->tokenType, "argurment")))
			set_as_command(command, tokens->token);
		else if (!ft_strcmps(tokens->tokenType, "pipe"))
			add_another_one(&command);
		else if ((!ft_strcmps(tokens->tokenType, "input"))
			|| (!ft_strcmps(tokens->tokenType, "output"))
			|| (!ft_strcmps(tokens->tokenType, "appaned"))
			|| (!ft_strcmps(tokens->tokenType, "herdoc")))
			handle_rediration(command, &tokens);
		tokens = tokens->next;
	}
	return (command_list);
}
