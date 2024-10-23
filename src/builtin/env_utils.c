#include "minishell.h"

t_env_list	*check_if_exit(t_env_list *list, char *str)
{
	t_env_list *node;

	node = list;
	while (node != NULL)
	{
		//problem here
		if ((ft_strncmp(str, node->name, ft_strlen(node->name))) == 0)
			return (node);
        node = node->next;
	}
	return (NULL);
}
