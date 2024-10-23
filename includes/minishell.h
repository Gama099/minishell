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

typedef struct s_file
{
	char    	*name;
	char    	*redirec;
	int     	fd[2];
	struct s_file *next;
} t_files;

typedef struct s_command
{
	char    	**argumants;
	t_files 	*files;
	struct s_command    *next;
} t_command;

typedef struct s_env_list
{
	char	*name;
	char	*value;
	int	type;
	struct s_env_list    *next;
} t_env_list;

typedef struct s_bash
{
	t_env_list	*list;
	t_command	cmd;
	t_files		*files;
	int			fd_stdin;
	int			fd_stdout;
} t_bash;

t_bash	*ft_bash(void);
char    *redirec_out(t_command *cmd, t_env_list *env);
char    *redirec_app_out(t_command *cmd, t_env_list *env);
char    *redirec_input(t_command *cmd, t_env_list *env);

// builtins
void		print_export(t_env_list *list);
int			ft_export(t_env_list *list, char **argv);
int			ft_env(t_env_list *list);
int			ft_unset(char **argv, t_env_list *list);
int			ft_echo(char **argv);
int 		ft_pwd();
int			ft_cd(char **arg);
int			ft_exit(char **arg);
int			check_if_builts(char **argv);
void		run_builts(char **argv, int argc, t_env_list *list);
int			there_is_plus(char *str);
int			check_value(char *str);
int 		set_under_score(char **argv);
t_env_list	*check_if_exit(t_env_list *list, char *str);
//builtins

//string_utils
size_t		ft_strlen(char *str);
char		*ft_strdup(const char *s1);
char		*ft_strnstr(const char	*big, const char *little, size_t len);
char    	*ft_strcpy(char *s1, char *s2);
char		*ft_strjoin(char *s1, char *s2);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char   		*find_path(char **env, char *cmd);
int			ft_isalnum(char c);
int			ft_isalpha(char c);
int     	check_access(char *PATH);
//string_utils

//syscall
void	 	ft_dup(int old_fd, int new_fd);
//syscall

//node
void		node_check(char	*str, t_env_list *node);
t_env_list	*env_to_list(char	**env);
t_env_list	*ft_create_node(char *str, int i);
t_env_list	*ft_last_node(t_env_list *head);
//node

# endif
