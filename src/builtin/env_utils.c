#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	i = 0;
	while (s1 && s2 && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

t_env_list	*check_if_exit(t_env_list *list, char *str)
{
	t_env_list *node;
	char **splited;

	node = list;
	if (there_is_plus(str) == 0)
		splited = ft_split(str, '+');
	else
		splited = ft_split(str, '=');
	while (node != NULL)
	{
		//problem here
		if ((ft_strcmp(node->name, splited[0])) == 0)
			return (node);
        node = node->next;
	}
	return (NULL);
}
