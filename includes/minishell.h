/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:15:12 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:15:14 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_memoryblock
{
	void					*ptr;
	size_t					size;
	struct s_memoryblock	*next;
}	t_memoryblock;

typedef struct s_tokens
{
	char			*token;
	char			*tokentype;
	int				qoute_type;
	int				join_with_next;
	int				expand_env;
	struct s_tokens	*next;
}	t_tokens;

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
	int				flag;
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
	t_memoryblock	*head;
	char			**env;
	t_env_list		*list;
	t_command		cmd;
	t_files			*files;
	int				fd_stdin;
	int				fd_stdout;
	int				exit_status;
}	t_bash;

typedef struct s_params
{
	char		*iter;
	int			in_qoutes;
	char		which_qoute;
	char		*token_begin;
	t_tokens	*tokens;
	int			to_join;
}	t_params;

//parser
void		cleanup(void);
int			is_word(char *token);
int			is_path(char *token);
int			checkcommand(char *token);
int			is_spaces(char *str);
void		hanlde_red(t_tokens **current, char *type);
void		parser(t_tokens **list);
t_tokens	*create_node_join(t_tokens *token_a, t_tokens *token_b);
int			free_token(t_tokens **token, t_tokens **iter, t_tokens **prev);
void		handle_j_with_n(t_tokens **token, t_tokens **iter, t_tokens **prev);
int			is_meta(char c);
int			is_qoute(char c);
void		create_tokens(t_tokens **token, char *str, int qoute, int to_join);
void		init_params(t_params *params, char *buffer);
void		start_qoute(t_params *params, char *buffer);
void		reach_space(t_params *params);
void		close_qoute(t_params *params);
void		reach_operator_a(t_params *params, char tmp);
void		reach_operator_b(t_params *params);
void		reach_operator(t_params *params);
void		reach_dollar(t_params *params, char *buffer);
t_tokens	*get_tokens(char *buffer, int sing_flag);
char		*ft_getenv(char *token);
void		creat_list(t_env_list **list, char *token);
int			count_evn_vars_len(t_env_list *list);
void		write_n_t(char *new_token, char *token_str, t_env_list *env_list);
int			get_env_len(char *env_var_start, t_env_list **env_list);
void		creat_list_state(t_env_list **list);
void		get_n_t_a(char **token_iter, t_env_list **env_list, int *token_len);
void		update_token(t_tokens *iter);
int			ft_strcmps(const char *s1, const char *s2);
int			is_operator(char *token);
int			handle_syntax_errors(t_tokens *tokens);
void		tokenaze_var(t_tokens **tokens);
void		createTokens(t_tokens **token, char *str, int qoute, int to_join);
t_tokens	*getTokens(char *buffer);
int			is_qoute_valid(char *buffer);
void		trim_spaces(char **buffer);
int			is_white_space(char charac);
char		*replace_var(char *token);
void		expand_varibles(t_tokens **token);
void		my_free(void *ptr);
void		*my_malloc(size_t	size);
t_command	*to_strcuct(t_tokens *tokens);
void		join_token_syblings(t_tokens **token);
char		*get_new_token(char *token_str);
void		clean_list_spaces(t_tokens **token);
int			handle_syntax_errors(t_tokens *tokens);
char		*ft_strcpy(char *dest, char *src);
void		initialize_argumants(t_command *command, char *arg);
void		handle_rediration(t_command *command, t_tokens **tokens);
t_command	*init_cmd_node(void);
int			ft_strcmps(const char *s1, const char *s2);
int			is_special_operator(char *tokentype);
int			is_operator(char *token);
int			check_first_token_is_pipe(t_tokens *tokens);
void		handle_dlr(char **w_ptr, char **str, t_env_list **ev_list);
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
char		*get_new_token_herodc(char *token_str);
char		*expand_herdoc(char *str);
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
char		*ft_strncpy(char *dest, const char *src, int n);
char		*ft_strrchr(const char *s, int c);
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
void		err_n_ex(char *err_mesg, char *err_cmd, char *err_name, int status);
void		err_msg(char *err_mesg, char *err_cmd, char *err_name);
//errors

//file
int			to_expand(char *input);
void		ambigous_helper(char	*file, int is_var);
int			redirect_no_cmd(t_files *file);
int			redirect_in_file_b_child(char *filename, int flag);
int			redirect_out_b_child(char *filename, int append, int flag);
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
void		update_env(char *name, char *value);
void		free_env(t_env_list *env);
t_env_list	*env_to_list(char	**env);
t_env_list	*ft_create_node(char *str, int mode);
t_env_list	*ft_last_node(t_env_list *head);
//node
#endif
