#include "../../../includes/minishell.h"

void	add_new_var(char *str, t_env_list *list)
{
	t_env_list	*new_node;
	t_env_list	*current;

	current = list;
	new_node = ft_create_node(str);
	if (new_node == NULL)
		return ;
	ft_last_node(current)->next = new_node;//add new var to env linked list
}

void	join_var(char *str, t_env_list *node)
{
	char	**splited;

	splited = ft_split(str, '=');
	node->name = ft_strjoin(node->name, splited[1]);
}

t_env_list	*check_if_exit(t_env_list *list, char *str)
{
	t_env_list *node;

	node = list;
	while (node != NULL)
	{
		if ((ft_strnstr(node->name, str, ft_strlen(str))) != NULL)
			return (node);
        node = node->next;
	}
	return (NULL);
}

int	there_is_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i - 1] == '+')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

void	change_var(char	*str, t_env_list *node)
{
	ft_strcpy(node->name, str);
}

int	before_sum(char *str, int i)
{
	int	j;

	j = 1;
	if (ft_isalpha(str[0]) != 1 || str[0] != '_')//alpha or underscore
		return (0);
	while (j <= i)
	{
		if (ft_isalnum(str[j]) != 1 || str[j] != '_')//alpha or numeric or underscore
			return (0);
		j++;
	}
	return (1);
}

int	arg_valid(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '=' || str[i])//
		i++;
	if (str[i] == '\0')//no = in the string
	{
		if (before_sum(str, i))//check if var is valid
			return (5);
		else
			return (EXIT_FAILURE);
	}
	if (there_is_plus(str))
	{
		if (before_sum(str, i - 2))//check if var is valid
			return (4);
		else
			return (EXIT_FAILURE);
	}
	else
	{
		if (before_sum(str, i - 1))
			return (3);
	}
	return (EXIT_FAILURE);
}

void	add_var(t_env_list *list, int i, char *str)
{
	t_env_list	*node;

	if ((node = check_if_exit(list, str) )!= NULL)
	{
		if (i == 5)
			ft();//dont do anything
		else if (i == 4)
			join_var(str, node);//appeand value
		else if (i == 3)
			change_var(str, node);//change value
	}
	add_new_var(str, list);
}

char	*ft_export(t_env_list *list, char **argv)
{
	int j;
	int	i;

	j = 2;
	if (argv[j] == NULL)// no args mean print
	{
		//print_export();
		return (NULL);
	}
	while (argv[j])
	{
		if ((i = arg_valid(argv[j])) != 1)
			add_var(list, i, argv[j]);
		else
			printf("bash: export: `%s': not a valid identifier\n",argv[j]);
		j++;
	}
	return (NULL);
}				