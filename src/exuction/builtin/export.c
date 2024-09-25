#include "../../../includes/minishell.h"

void	add_new_var(char *str, t_env_list *list)
{
	t_env_list	*new_node;
	t_env_list	*current;

	current = list;
	new_node = ft_create_node(str);
	ft_last_node(current)->next = new_node;//add new var to env linked list
}

char	*ft_export(t_env_list *list, char **argv)
{
	int j;

	j = 2;
	if (argv[j] == NULL)// no args mean print
	{
		//print_export();
		return (NULL);
	}
	while (argv[j])
	{
		add_new_var(argv[j], list);
		j++;
	}
	return (NULL);
}
