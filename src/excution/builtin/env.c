#include "../../../includes/minishell.h"

char	*ft_env(t_env_list *list)
{
	t_env_list	*new_node;

	new_node = list;
	while(new_node != NULL)
	{
		if (new_node->value == 1)
			printf("%s\n",new_node->name);
		new_node = new_node->next;
	}
	return ("succes");
}
