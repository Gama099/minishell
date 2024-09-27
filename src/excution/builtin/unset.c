#include "../../../includes/minishell.h"

char	*ft_unset(char **argv, t_env_list *list)
{
	t_env_list *new_node;
	t_env_list	*prev;
	int	j;

	j = 2;
	while (argv[j])
	{
		new_node = list;
		while ((ft_strcmp(new_node->name, argv[j])) == 1)
		{
			prev = new_node;
        	new_node = new_node->next;
		}
		prev->next = new_node->next;
		new_node->next = NULL;
		//delete node;
		j++;
	}
	return(NULL);
}
