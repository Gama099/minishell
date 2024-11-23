#include "../includes/minishell.h"

void	sigint_handler_main(int num)
{
	(void)num;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	init_status(130);
}

void	sigint_handler_cmd(int num)
{
	(void)num;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	init_status(130);
}

void	sigint_handler_hd(int num)
{
	(void)num;
	write(2, "\n", 1);
	clean_exit(130);
}

void	sigquit_handler_cmd(int num)
{
	(void) num;
	write(2, "Quit (core dumped)\n", 19);
	rl_on_new_line();
	rl_replace_line("", 0);
	init_status(131);
}
