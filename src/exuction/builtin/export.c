#include "../../../includes/minishell.h"

void	add_new_var(char *str, t_env_list *list)
{
	t_env_list	*new_node;
	t_env_list	*current;

	current = list;
	new_node = ft_create_node(str);
	ft_last_node(current)->next = new_node;//add new var to env linked list
}

void	join_var(char *str, t_env_list *node)
{
	char	**splited;

	splited = ft_split(str, '=');
	node->value = ft_strjoin(node->value, splited[1]);
}

t_env_list	*check_if_exit(t_env_list *list, char *str)
{
	int	i;
	t_env_list *node;

	node = list;
	i = 0;
	while (node != NULL)
	{
		if ((ft_strnstr(node->name, str, ft_strlen(str))) != NULL)
			return (node);
        node = node->next;
	}
	return (NULL);
}

int	there_is_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i - 1] == '+')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

void	change_var(char	*str, t_env_list *node)
{
	ft_strcpy(node->value, str);
}

char	*ft_export(t_env_list *list, char **argv)
{
	int j;
	t_env_list	*node;
	
	j = 2;
	if (argv[j] == NULL)// no args mean print
	{
		//print_export();
		return (NULL);
	}
	while (argv[j])
	{
		// check if var exit
		// then check if there is + before =
		// if += for old var join else create new var
		//if = for old var change value else add new var
		if ((node = check_if_exit(list,argv[j]) )!= NULL)
		{
			if (there_is_plus(argv[j]))
				join_var(argv[j], node);
			else
				change_var(argv[j], node);
		}
		add_new_var(argv[j], list);
		j++;
	}
	return (NULL);
}
