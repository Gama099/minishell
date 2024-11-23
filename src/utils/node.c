#include "../../includes/minishell.h"

t_env_list	*ft_last_node(t_env_list *head)
{
	t_env_list	*new_node;

	new_node = head;
	while (new_node->next != NULL)
		new_node = new_node->next;
	return (new_node);
}

void	free_ary(char	**str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	str = NULL;
}

void	fill_node(t_env_list *node, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	node->value = ft_substr_h(str, i + 1, ft_strlen(str));
	if (!there_is_plus(str))
		node->name = ft_substr_h(str, 0, i - 1); //remove + from 1 array after the split
	node->name = ft_substr_h(str, 0, i);
}

t_env_list	*ft_create_node(char *str)
{
	t_env_list	*new_node;
	int			flag;

	new_node = malloc(sizeof(t_env_list));
	if (!new_node)
		err_n_exit("syscall failed", "malloc", NULL, 1);
	fill_node(new_node, str);
	flag = check_value(str);
	if (flag == 0 || flag == 2) // there is = sometimes with value sometimes not
		new_node->type = 1;
	else
		new_node->type = 0;
	new_node->next = NULL;
	return (new_node);
}

void	update_sh(t_env_list *list)
{
	t_env_list	*node;
	char		*tmp;

	node = check_if_exit(list, "SHLVL", 2);
	if (node != NULL)
	{
		tmp = node->value;
		node->value = ft_itoa(ft_atoi(node->value) + 1);
		free(tmp);
		tmp = NULL;
	}
}

t_env_list	*env_to_list(char	**env)
{
	int			i;
	t_env_list	*current;
	t_env_list	*new_node;
	t_env_list	*first;

	i = 0;
	current = NULL;
	while (env[i])
	{
		new_node = ft_create_node(env[i]);
		if (current == NULL)
		{
			current = new_node;
			first = current;
		}
		else
			ft_last_node(current)->next = new_node;
		i++;
	}
	update_sh(first);
	return (first);
}

void	free_env(t_env_list *env)
{
	t_env_list	*tmp;

	while (env != NULL)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		tmp->name = NULL;
		free(tmp->value);
		tmp->value = NULL;
		free(tmp);
		tmp = NULL;
	}
	env = NULL;
}

void	free_struct(t_command	*cmd)
{
	t_command	*tmp;
	t_files		*tmp2;

	while (cmd != NULL)
	{
		while (cmd->files != NULL)
		{
			tmp2 = cmd->files;
			cmd->files = cmd->files->next;
			free(tmp2->name);
			tmp2->name = NULL;
			free(tmp2->redirec);
			tmp2->redirec = NULL;
			free(tmp2);
			tmp2 = NULL;
		}
		tmp = cmd;
		cmd = cmd->next;
		free_ary(tmp->args);
		free(tmp);
		tmp = NULL;
	}
	cmd = NULL;
}
