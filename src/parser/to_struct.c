#include "../../includes/minishell.h"


/*void	set_at_command(t_command *command, char *arg)
{
	int		i;
	char	**tmp;
	int		new_len;

	i = 0;
	if (command->argumants == NULL)
	{
		command->argumants = malloc(sizeof(char *) * 2);
		{
			command->argumants[0] = ft_strdup(arg);
			command->argumants[1] = NULL;
		}
	}
	else
	{
		while (command->argumants[i])
			i++;
		new_len = i + 2;
		tmp = malloc(sizeof(char *) * new_len);
		i = 0;
		while (command->argumants[i])
		{
			tmp[i] = ft_strdup(command->argumants[i]);
			i++;
		}
		tmp[i++] = ft_strdup(arg);
		tmp[i] = NULL;
		i = 0;
		while (command->argumants[i])
			free(command->argumants[i++]);
		free(command->argumants[i]);
		free(command->argumants);
		command->argumants = tmp;
	}
}

void	add_another_one(t_command **command)
{
	t_command *new_node;

	new_node = malloc(sizeof(t_command));
	(*command)->next = new_node;
	new_node->argumants = NULL;
	new_node->next = NULL;
	new_node->files.name = NULL;
	new_node->files.next = NULL;
	new_node->files.redirec = NULL;
	new_node->files.fd[0] = -1;
	new_node->files.fd[1] = -1;
}

t_command	*to_strcuct(t_tokens *tokens)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	command->argumants = NULL;
	command->next = NULL;
	command->files.name = NULL;
	command->files.next = NULL;
	command->files.redirec = NULL;
	command->files.fd[0] = -1;
	command->files.fd[1] = -1;
	//to have the head of list
	t_command *head = command;
	while (tokens)
	{
		if ((!ft_strncmp(tokens->tokenType, "command", ft_strlen("command"))) || (!ft_strncmp(tokens->tokenType, "argurment", ft_strlen("argurment"))))
			set_at_command(command, tokens->token);

		else if (!ft_strncmp(tokens->tokenType, "pipe", ft_strlen("pipe")))
		{
			add_another_one(&command);
			command = command->next;
		}

		else if((!ft_strncmp(tokens->tokenType, "input", ft_strlen("input")))
			|| (!ft_strncmp(tokens->tokenType, "output", ft_strlen("output"))) ||
			(!ft_strncmp(tokens->tokenType, "appaned", ft_strlen("appaned"))))
		{
			if (command->files.redirec == NULL)
			{
				command->files.redirec = ft_strdup(tokens->token);
				tokens = tokens->next;
				if (tokens)
					command->files.name = ft_strdup(tokens->token);
			}
			else
			{
				t_files *new_file;
				t_files *current;

				current = &command->files;
				new_file = malloc(sizeof(t_files));
				new_file->redirec = ft_strdup(tokens->token);
				new_file->fd[0] = -1;
				new_file->fd[1] = -1;
				tokens = tokens->next;
				if (tokens)
					new_file->name = ft_strdup(tokens->token);
				while (current->next)
					current = current->next;
				current->next = new_file;
			}
		}
		tokens = tokens->next;
	}
	return (head);
}

/*int main()
{
	t_tokens	token;
	t_command	*command;
	token.token = ft_strdup("token");
	token.tokenType = ft_strdup("command");
	token.next = malloc(sizeof(t_tokens));
	token.next->token = ft_strdup("|");
	token.next->tokenType = ft_strdup("pipe");
	token.next->next = malloc(sizeof(t_tokens));
	token.next->next->token = ft_strdup("echo");
	token.next->next->tokenType = ft_strdup("command");
	token.next->next->next = malloc(sizeof(t_tokens));
	token.next->next->next->token = ft_strdup("file");
	token.next->next->next->tokenType = ft_strdup("input_rediraction");
	token.next->next->next->next = NULL;
	command = to_strcuct(&token);
	while (command)
	{
		int i;

		i = 0;
		while (command->argumants[i])
			printf("%p->%s\n", command, command->argumants[i++]);
		command = command->next;
	}
}
*/

t_command	*init_cmd_node(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	command->argumants = NULL;
	command->next = NULL;
	command->files = malloc(sizeof(t_files));
	command->files->name = NULL;
	command->files->next = NULL;
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
		//TODO
		new_file->fd[0] = -1;
		new_file->fd[1] = -1;
		while (current->next)
			current = current->next;
		current->next = new_file;
		current = new_file;
	}
	current->redirec = ft_strdup((*tokens)->token);
		(*tokens) = (*tokens)->next;
	if (*tokens)
		current->name = ft_strdup((*tokens)->token);
	if ((*tokens)->qoute_type)
		command->files->expand_flag = (*tokens)->qoute_type;
	//printf("[command->files->expand_flag == %d]\n", command->files->expand_flag);
}

void	set_as_command(t_command *command, char *arg)
{
	int		i;
	char	**tmp;
	int		new_len;

	i = 0;
	if (command->argumants == NULL)
	{
		command->argumants = malloc(sizeof(char *) * 2);
		{
			command->argumants[0] = ft_strdup(arg);
			command->argumants[1] = NULL;
		}
	}
	else
	{
		while (command->argumants[i])
			i++;
		new_len = i + 2;
		tmp = malloc(sizeof(char *) * new_len);
		i = 0;
		while (command->argumants[i])
		{
			tmp[i] = ft_strdup(command->argumants[i]);
			i++;
		}
		tmp[i++] = ft_strdup(arg);
		tmp[i] = NULL;
		i = 0;
		while (command->argumants[i])
			free(command->argumants[i++]);
		free(command->argumants[i]);
		free(command->argumants);
		command->argumants = tmp;
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
