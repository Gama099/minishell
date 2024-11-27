# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_tokens
{
	char	*token;
	char	*tokenType;
	int		qoute_type;
	int		join_with_next;
	int		expand_env;
	struct s_tokens *next;
} t_tokens;

typedef struct s_env_var
{
  char *var;
  char *real_value;
  struct s_env_var  *next;
} t_env_var;

typedef struct s_env_list
{
	char	*name;
	char	*value;
	int	type;
	struct s_env_list    *next;
} t_env_list;

//expand functions
char *ft_getenv(char *token);
void creat_list(t_env_list **list, char *token);
int count_evn_vars_len(t_env_list *list);
void write_new_token(char *new_token, char *token_str, t_env_list *env_list);
int get_env_len(char *env_var_start, t_env_list **env_list);
void creat_list_state(t_env_list **list, char *token);
void get_new_token_a(char **token_iter, t_env_list **env_list, int *token_len);
char *get_new_token(char *token_str);
void update_token(t_tokens *iter);
void expand_varibles(t_tokens **token);
