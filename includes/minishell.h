#ifndef MINISHELL_H
# define MINISHEL_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>


char	*ft_strnstr(const char	*big, const char *little, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char    *find_path(char **env, char *cmd);
size_t	ft_strlen(char *str);
int check_access(char *PATH);

# endif
