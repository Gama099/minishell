#include "../../includes/minishell.h"

void	add_new_var(char *str, t_env_list *list)
{
	t_env_list	*new_node;
	t_env_list	*current;
	char	*tmp;

	current = list;
	new_node = ft_create_node(str);
	if (new_node == NULL)
		return ;
	if (check_value(str) == 2)
	{
		tmp = new_node->value;
		new_node->value = ft_strdup("");
		free(tmp);
		tmp = NULL;
	}
	ft_last_node(current)->next = new_node; //add new var to env linked list
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
	free_ary(splited);
}

void	change_var(char	*str, t_env_list *node)
{
	char	**splited;
	char	*tmp;

	splited = ft_split(str, '=');
	if (check_value(str) == 2)
	{
		tmp = node->value;
		node->value = ft_strdup("");
		free(tmp);
	}
	if (check_value(str) == 0)
	{
		node->type = 1;
		tmp = node->value;
		node->value = ft_strdup(splited[1]);
		free(tmp);
	}
	free_ary(splited);
	tmp = NULL;
}

void	check_var(t_env_list *list, int i, char *str)
{
	t_env_list	*node;

	node = check_if_exit(list, str, 1);
	if (node != NULL)
	{
		if (i == 5)
			return ; //dont do anything
		else if (i == 6)
			node->value = ft_strdup("");
		else if (i == 4)
			join_var(str, node); //appeand value
		else if (i == 3)
			change_var(str, node);//change value
	}
	else
		add_new_var(str, list);
}

int	ft_export(char **str)// fix var var1 var2
{
	int	j;
	int	i;
	int	status;

	j = 1;
	status = 0;
	if (str[j] == NULL) // no args mean sort and print
	{
		print_export(ft_bash()->list);
		return (0);
	}
	while (str[j])
	{
		i = arg_valid(str[j]);
		if (i != 1)
			check_var(ft_bash()->list, i, str[j]);
		else
		{
			err_msg("not a valid identifier", "export", str[j]);
			status = 1;
		}
		j++;
	}
	return (status);
}
