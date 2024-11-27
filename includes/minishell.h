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
# include <signal.h>

typedef struct s_tokens
{
	char			*token;
	char			*tokenType;
	int				qoute_type;
	int				join_with_next;
	int				expand_env;
	struct s_tokens	*next;
} t_tokens;

typedef struct s_env_var
{
	char				*var;
	char				*real_value;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_listo
{
	void			*ptr;
	int				size;
	struct s_listo	*next;
}	t_listo;

typedef struct s_file
{
	int				flag; // 0 = no qoutes, 1 = ' , 2 = ""
	char			*name;
	char			*redirec;
	int				fd[2];
	struct s_file	*next;
}	t_files;

typedef struct s_pipes
{
	int	*pid;
	int	j;
}	t_pipes;

typedef struct s_command
{
	char				**args;
	t_files				*files;
	struct s_command	*next;
}	t_command;

typedef struct s_env_list
{
	char				*name;
	char				*value;
	int					type;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_bash
{
	char		**env;
	t_env_list	*list;
	t_command	cmd;
	t_files		*files;
	int			fd_stdin;
	int			fd_stdout;
	int			exit_status;
}	t_bash;


//parser
int			is_spaces(char *str);
int			ft_strcmps(const char *s1, const char *s2);
int			is_operator(char *token);
int			handle_syntax_errors(t_tokens *tokens);
void		tokenaze_var(t_tokens **tokens);
void		createTokens(t_tokens **token, char *str, int qoute, int to_join);
t_tokens	*getTokens(char *buffer);
int			is_qoute_valid(char *buffer);
void		trimSpaces(char **buffer);
int			is_white_space(char charac);
void		parser(t_tokens **list);
char		*replace_var(char *token);
void		expand_varibles(t_tokens **token);
void		my_free(void);
void		*my_malloc(size_t	size);
t_command	*to_strcuct(t_tokens *tokens);
void		join_token_syblings(t_tokens **token);
char		*get_new_token(char *token_str);
void    	clean_list_spaces(t_tokens **token);
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
int			ft_pwd(void);
int			ft_cd(char **arg);
int			ft_exit(char **arg);
int			run_builts(t_command *cmd);
int			there_is_plus(char *str);
int			check_value(char *str);
int			set_under_score(char **argv);
int			redirect_builtin(t_command *cmd);
t_env_list	*check_if_exit(t_env_list *list, char *str, int mode);
//builtins

//excution
int			spaces(t_command *cmd);
int			excution_parse(t_command *cmd);
int			excution_status(int status);
int			no_cmd(t_command *cmd);
char		*get_path(void);
int			red_counter(t_command	*cmd);
char		**split_env(void);
t_bash		*ft_bash(void);
int			redirect_file(t_command *cmd);
int			check_path(t_command *cmd);
int			counter(void *count, int mode);
char		*get_redarct(t_command *cmd, int *pipe, int input);
int			one_cmd(t_command *cmd, int input, int *pipe);
int			excution_pipe(t_command *cmd);
void		ft_env_i(void);
char		*find_path(char *cmd);
int			excution(t_command *cmd);
char		**env_to_ary(t_env_list *envp);
int			check_access(char *path);
//excution

//string_utils
char		*ft_substr_h(char *s, int start, int end);
int			ft_strlen(const char *str);
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
int			ft_putstr_fd(char *s, int fd);
void		ft_bzero(void *s, size_t n);
int			ft_strcmp(char *s1, char *s2);
char		*ft_itoa(int n);
//string_utils

//syscall
void		ft_close(int fd);
int			ft_fork(void);
void		init_status(int status);
void		save_stdfd(void);
void		ft_dup(int old_fd, int new_fd);
void		revert_stdfd(void);
//syscall

//errors
void		clean_exit(int exit_status);
void		err_n_exit(char *err_mesg, char *err_cmd, char *err_name, int status);
void		err_msg(char *err_mesg, char *err_cmd, char *err_name);
//errors

//file
int			to_expand(char *input);
void		ambigous_helper(char	*file, int is_var);
int			redirect_no_cmd(t_files *file);
int			redirect_in_file_b_child(char *filename, int flag);
int			redirect_out_b_child(char *filename, int append, int flag);
void		free_ary(char	**str);
int			ft_herdoc(t_command	*cmd);
int			check_ambiguous(char **filename, int flag);
int			is_a_directory(char *filename, int bltn);
char		*expand_name(char *file);
//file

//signals
void		sigint_handler_main(int num);
void		sigint_handler_cmd(int num);
void		sigint_handler_hd(int num);
void		sigquit_handler_cmd(int num);
//signals

//node
void		fill_node(t_env_list *node, char *str, int mode);
void		free_struct(t_command	*cmd);
void		update_env(char *name, char *value);
void		free_env(t_env_list *env);
t_env_list	*env_to_list(char	**env);
t_env_list	*ft_create_node(char *str, int mode);
t_env_list	*ft_last_node(t_env_list *head);
//node
#endif
