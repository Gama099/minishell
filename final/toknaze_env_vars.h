
//tokanze env vars
t_tokens *create_node_join(t_tokens *token_a, t_tokens *token_b);
int free_token(t_tokens **token, t_tokens **iter, t_tokens **prev);
void handle_join_with_next(t_tokens **token, t_tokens **iter, t_tokens **prev);
void join_token_syblings(t_tokens **token);
