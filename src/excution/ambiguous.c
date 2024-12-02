/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:11:39 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:11:41 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_name(char *file)
{
	char		*str;

	if (ft_strchrr(file, '$') == -1)
		return (file);
	str = get_new_token(file);
	if (str == NULL || str[0] == ' ')
		return (NULL);
	return (str);
}

void	ambigous_helper(char *file, int is_var)
{
	char	*ex_file;
	char	**spl_ex_file;

	ex_file = expand_name(file);
	if (ex_file != NULL)
	{
		spl_ex_file = ft_split(ex_file, ' ');
		if (is_var && (spl_ex_file[0] != NULL && spl_ex_file[1] != NULL))
			err_n_ex("ambiguous redirection", NULL, file, 1);
		spl_ex_file = ft_split(ex_file, '	');
		if (is_var && (spl_ex_file[0] != NULL && spl_ex_file[1] != NULL))
			err_n_ex("ambiguous redirection", NULL, file, 1);
	}
	else if (is_var && ex_file == NULL && ft_strlen(file) > 1)
		err_n_ex("ambiguous redirection", NULL, file, 1);
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
		if (check == 1)
			err_n_ex(NULL, NULL, cmd->args[0], 127);
		else if (check == 2)
			err_n_ex(NULL, NULL, cmd->args[0], 126);
		else
			return (3);
	}
	return (check);
}

int	set_under_score(char **argv)
{
	t_env_list	*var;
	char		*value;
	int			i;

	i = 0;
	while (argv[i])
		i++;
	if (i == 0)
		return (1);
	value = ft_strdup(argv[i - 1]);
	var = check_if_exit(ft_bash()->list, ft_strdup("_"), 0);
	if (var)
	{
		if (value)
			var->value = value;
	}
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
