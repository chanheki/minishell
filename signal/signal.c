
#include <signal.h>
#include "../include/minishell.h"

void	sigint_heredoc(int signo)
{
	(void)signo;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_var.is_signal = 1;
	g_var.exit_status = 1;
}

void	sigint_prompt(int signumber)
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
	if (signal(SIGINT, sigint_prompt) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		g_var.exit_status = (int)SIG_ERR;
}
