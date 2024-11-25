#include "../../includes/minishell.h"

char	*expand_name(char *file)
{
	char		*str;

	if (ft_strchrr(file, '$') == -1)
		return (file);
	str = get_new_token(file);
	if (str == NULL || str[0] == ' ') // erorr here
		return (free(str), NULL);
	return (str);
}

void	ambigous_helper(char	*file, int is_var)
{
	char	*ex_file;
	char	**spl_ex_file;

	ex_file = expand_name(file);
	if (ex_file != NULL)
	{
		spl_ex_file = ft_split(ex_file, ' ');
		if (is_var && (spl_ex_file[0] != NULL && spl_ex_file[1] != NULL))
		{
			free(ex_file);
			free_ary(spl_ex_file);
			err_n_exit("ambiguous redirection", NULL, file, 1);
		}
		free_ary(spl_ex_file);
	}
	else if (is_var && ex_file == NULL && ft_strlen(file) > 1) // if both != NULL that mean there was space
	{
		free(ex_file);
		err_n_exit("ambiguous redirection", NULL, file, 1);
	}
}

int	check_path(t_command *cmd)
{
	int	check;

	check = 0;
	if (ft_strchrr(cmd->args[0], '/') != -1)
	{
		if (is_a_directory(cmd->args[0], 1))
			clean_exit(126);
		check = check_access(cmd->args[0]);
		if (check == 1) // not found
			err_n_exit(NULL, NULL, cmd->args[0], 127);
		else if (check == 2) //not excutable
			err_n_exit(NULL, NULL, cmd->args[0], 126);
		else
			return (3); //path is valid
	}
	return (check);
}

int	set_under_score(char **argv) //to be fixed
{
	char		*value;
	int			i;

	i = 0;
	while (argv[i])
		i++;
	if (i == 0)
		return (1);
	value = ft_strdup(argv[i - 1]);
	update_env(ft_strdup("_"), value);
	return (0);
}

int	to_expand(char *input)
{
	if (input[0] == '$' || input[0] == '\'')
		return (1);
	if (input[0] == '\"')
		return (1);
	return (0);
}
