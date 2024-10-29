#include "../../includes/minishell.h"

int	check_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1] != '\0')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

t_env_list	*ft_last_node(t_env_list *head)
{
	t_env_list	*new_node;

	new_node = head;
	while (new_node->next != NULL)
		new_node = new_node->next;
	return (new_node);
}

t_env_list	*ft_create_node(char *str)
{
	t_env_list	*new_node;
	int	flag;

	new_node = malloc(sizeof(t_env_list));
	if (!new_node)
		return (NULL);
	new_node->name = str;
	if ((flag = check_value(str)) == 0)
		new_node->value = 1;
	else
		new_node->value = 0;
	new_node->next = NULL;
	return (new_node);
}

t_env_list	*env_to_list(char	**env)
{
	int	i;
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
	return (first);
}

void	free_env(t_env_list *env)
{
	t_env_list *tmp;

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
