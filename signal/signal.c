
#include <signal.h>
#include "../include/minishell.h"

extern t_global	g_var;

static void	sigint_prompt_handler(int signumber)
{
	if (signumber == SIGINT)
	{
		g_var.exit_status = 1;
		rl_replace_line("", 1);
		ft_putendl_fd("", STDOUT_FILENO);
		if (rl_on_new_line() == FAIL)
			exit(EXIT_FAILURE);
		rl_redisplay();
	}
}

void	set_signal(void)
{
	rl_catch_signals = 0;
	if (signal(SIGINT, sigint_prompt_handler) == SIG_ERR ||
			signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
}
