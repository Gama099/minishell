#include "../../includes/minishell.h"

int	is_a_directory(char *filename, int bltn)
{
	struct stat	buff;

	ft_bzero(&buff, sizeof(buff));
	stat(filename, &buff);
	if ((buff.st_mode & __S_IFMT) == __S_IFDIR)
	{
		printf("Is a directory\n");
		if (bltn == 0)
			clean_exit(1);
		return (1);
	}
	return (0);
}

int	check_ambiguous(char *filename)
{
	if ((filename == NULL || ft_strchrr(filename, ' ') != -1))
		return (err_msg("ambiguous redirection", NULL, NULL), 1);
	return (0);
}
