
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

typedef struct s_params
{
	char 		*iter;
	int			in_qoutes;
	char		which_qoute;
	char		*token_begin;
    t_tokens	*tokens;
	int			to_join;
} t_params;

// tokenazation funtions
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
t_tokens	*get_tokens(char *buffer);
