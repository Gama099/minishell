#include "../../includes/minishell.h"

int	ft_env(t_env_list *list , char **str)
{
	t_env_list	*new_node;
	int		i;

	new_node = list;
	i = 0;
	while (str[i])
		i++;
	if (i > 1)
		return (printf("too many arguments\n"), 1);
	while(new_node != NULL)
	{
		if (new_node->type == 1)
		{
			printf("%s",new_node->name);
			printf("=%s\n",new_node->value);
		}
		new_node = new_node->next;
	}
	return (0);
}
