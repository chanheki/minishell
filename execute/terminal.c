#include "../include/minishell.h"

void	set_terminal_attribute(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_var.new_term));
}

void	get_terminal_setting(void)
{
	tcgetattr(STDIN_FILENO, &(g_var.old_term));
	tcgetattr(STDIN_FILENO, &(g_var.new_term));
	g_var.new_term.c_lflag &= ~ECHOCTL;
	g_var.new_term.c_cc[VQUIT] = 0;
	set_terminal_attribute();
}
