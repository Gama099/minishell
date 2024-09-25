#include "../../../includes/minishell.h"

char	*ft_unset(char **argv, t_env_list *list)
{
	t_env_list *new_node;
	t_env_list	*prev;
	int	j;
	char	**splited;

	j = 2;
	while (argv[j])
	{
		new_node = list;
		splited = ft_split(argv[j]);
		while ((ft_strnstr(new_node->name, splited[0], ft_strlen(splited[0]))) == NULL)
		{
			prev = new_node;
        	new_node = new_node->next;
		}
		prev->next = new_node->next;
		j++;
	}
	return(NULL);
}
