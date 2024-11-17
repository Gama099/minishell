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
	char	**splited;
	char	*name;
	char	*value;

	splited = ft_split(str, '=');
	value = ft_strdup(splited[1]);
	node->value = value;
	if (!there_is_plus(str))
		splited[0][ft_strlen(splited[0]) - 1] = '\0'; //remove + from 1 array after the split
	name = ft_strdup(splited[0]);
	node->name = name;
	free_ary(splited);
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
