#include "minishell.h"

void	add_new_var(char *str, t_env_list *list)
{
	t_env_list	*new_node;
	t_env_list	*current;

	current = list;
	new_node = ft_create_node(str, 1);
	if (new_node == NULL)
		return ;
	if (check_value(str) == 2)
		new_node->value = ft_strdup("");
	ft_last_node(current)->next = new_node;//add new var to env linked list
}

void	join_var(char *str, t_env_list *node)
{
	char	**splited;

	splited = ft_split(str, '=');
	if (node->value == NULL)
	{
		node->type = 1;
		node->value = ft_strdup(splited[1]);
	}
	else
		node->value = ft_strjoin(node->value, splited[1]);
}

void	change_var(char	*str, t_env_list *node)
{
	char	**splited;
	
	splited = ft_split(str, '=');
	if (check_value(str) == 2)
		node->value = ft_strdup("");
	if (check_value(str) == 0)
	{
		node->type = 1;
		node->value = splited[1];
	}
}

void	check_var(t_env_list *list, int i, char *str)
{
	t_env_list	*node;

	if ((node = check_if_exit(list, str) )!= NULL)
	{
		if (i == 5)
			return ;//dont do anything
		else if (i == 4)
			join_var(str, node);//appeand value
		else if (i == 3)
			change_var(str, node);//change value
	}
	else
		add_new_var(str, list);
}

int		ft_export()
{
	int j;
	int	i;

	j = 1;
	if (ft_bash()->cmd.argumants[j] == NULL)// no args mean sort and print
	{
		print_export(ft_bash()->list);
		return (0);
	}
	while (ft_bash()->cmd.argumants[j])
	{
		if ((i = arg_valid(ft_bash()->cmd.argumants[j])) != 1)
			check_var(ft_bash()->list, i, ft_bash()->cmd.argumants[j]);
		else
			printf("bash: export: `%s': not a valid identifier\n",ft_bash()->cmd.argumants[j]);
		j++;
	}
	return (0);
}