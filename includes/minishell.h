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
# include <limits.h>

typedef struct t_file
{
char    *fillName;
char    *redirec;
int     fd[2];
} t_files;

typedef struct s_command
{
char    **argumants;
t_files files;
struct s_command    *next;
} t_command;

typedef struct s_env_list
{
	char	*name;
	int	value;
struct s_env_list    *next;
} t_env_list;

void	run_builts(char **argv, int argc, t_env_list *list);
char	*ft_strnstr(const char	*big, const char *little, size_t len);
char	*ft_export(t_env_list *list, char **argv);
char	*ft_env(t_env_list *list);
char	*ft_unset(char **argv, t_env_list *list);
char    *ft_echo(char **argv , int argc);
char    *ft_strcpy(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char    *find_path(char **env, char *cmd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int 	ft_pwd();
int		check_value(char *str);
int		echo_check(char **argv, int argc);
int		check_if_builts(char **argv);
int		ft_isalnum(char c);
int		ft_isalpha(char c);
int     check_access(char *PATH);
size_t	ft_strlen(char *str);
t_env_list	*ft_create_node(char *str);
t_env_list	*ft_last_node(t_env_list *head);

# endif
