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
	while (str && str[i])
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
