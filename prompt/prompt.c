
#include "../include/minishell.h"

extern t_global	g_var;

static void	get_terminal_setting(void)
{
	tcgetattr(STDIN_FILENO, &(g_var.old_term));
	tcgetattr(STDIN_FILENO, &(g_var.new_term));
	g_var.new_term.c_lflag &= ~ECHOCTL;
	g_var.new_term.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_var.new_term));
}

void	initialize_setting()
{
	ft_putstr_fd(JIPHEADER, 2);
	set_signal();
	get_terminal_setting();
}

void	initialize_global_variable(int argc, char **argv, char **env)
{
	g_var.argv = argv;
	g_var.argc = argc;
	g_var.envp = env;
	g_var.exit_status = 0;
}

void	validator()
{	
	if (g_var.exit_status == -1)
	{
		ft_putendl_fd("JIP-shell: Terminal Setting Error", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (g_var.argc > 1)
	{
		ft_putendl_fd("JIP-shell: Do not support this mode", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	check_eof(char *str)
{
	if (str == NULL)
	{
		ft_putendl_fd("\x1b[1A\033[12Cexit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}
