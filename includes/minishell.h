#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/stat.h>

typedef struct s_tokens
{
	char	*token;
	char	*tokenType;
	int		sing_qoute;
	int		join_with_next;
	struct s_tokens *next;
} t_tokens;

typedef struct s_env_var
{
  char *var;
  char *real_value;
  struct s_env_var  *next;
} t_env_var;

  typedef struct s_listo
{
	void	*ptr;
	int		size;
	struct s_listo	*next;
}	t_listo;

typedef struct s_file
  {
  char    *name;
  char    *redirec;
  int     fd[2];
  struct s_file *next;
  } t_files;

  typedef struct s_command
  {
  char    **argumants;
  t_files *files;
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
	char		**env;
	t_env_list	*list;
	t_command	cmd;
	t_files		*files;
	int			fd_stdin;
	int			fd_stdout;
} t_bash;

t_bash		*ft_bash(void);
int			redirect_file(t_command *cmd);

//parser

void	createTokens(t_tokens **token, char *str, int qoute, int to_join);
t_tokens *getTokens(char *buffer);
int is_qoute_valid(char *buffer);
void	trimSpaces(char **buffer);
int	is_white_space(char charac);
void    parser(t_tokens **list);
char	*replace_var(char *token);
void	expand_varibles(t_tokens **token);
void	my_free(void);
void	*my_malloc(size_t	size);
t_command	*to_strcuct(t_tokens *tokens);
void	join_token_syblings(t_tokens **token);
//parser

// builtins
void		print_export(t_env_list *list);
void		child_builtin_helper(t_command *cmd, int input, int *pipe);
int			builtin_helper(t_command *cmd);
int			check_if_builts(char *cmd);
int			ft_export(char **str);
int			arg_valid(char *str);
int			ft_env(t_env_list *list, char **str);
int			ft_unset(char **argv, t_env_list **list);
int			ft_echo(char **argv);
int 		ft_pwd();
int			ft_cd(char **arg);
int			ft_exit(char **arg);
int			run_builts(t_command *cmd);
int			there_is_plus(char *str);
int			check_value(char *str);
int 		set_under_score(char **argv);
int			redirect_builtin(t_command *cmd);
t_env_list	*check_if_exit(t_env_list *list, char *str);
//builtins

//excution
char   		*find_path(char *cmd);
int			excution(t_command *cmd);
//excution

//string_utils
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strdup(char *s1);
char		*ft_strnstr(const char	*big, const char *little, size_t len);
char		*ft_strjoin(char *s1, char *s2);
char		**ft_split(char const *s, char c);
int			ft_atoi(char *str);
int			ft_putchar_fd(char c, int fd);
int			ft_putendl_fd(char *s, int fd);
int			ft_strchrr(char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isalnum(char c);
int			ft_isalpha(char c);
int			ft_isdigit(char a);
int     	check_access(char *PATH);
int			ft_putstr_fd(char *s, int fd);
void		ft_bzero(void *s, size_t n);
//string_utils

//syscall
void		save_stdfd(void);
void	 	ft_dup(int old_fd, int new_fd);
void		revert_stdfd(void);
//syscall

//errors
void		clean_exit(int exit_status);
void		err_n_exit(char *err_msg, char *err_cmd, char *err_name, int status);
void		pr_err_msg(char *err_msg, char *err_cmd, char *err_name);
//errors

//file
int			is_a_directory(char *filename, int bltn);
//file

//node
void		node_check(char	*str, t_env_list *node);
void		free_env(t_env_list *env);
t_env_list	*env_to_list(char	**env);
t_env_list	*ft_create_node(char *str);
t_env_list	*ft_last_node(t_env_list *head);
//node
# endif
