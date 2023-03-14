
#include "../include/minishell.h"

extern t_global	g_var;

void	initialize_setting()
{
	ft_putstr_fd(MINISHELLHEADER, 2);
	set_signal();
}

void	initialize_global_variable(int argc, char **argv, char **env)
{
	g_var.argv = argv;
	g_var.argc = argc;
	g_var.envp = env;
	g_var.exit_status = 0;
}

void validator()
{	
	// g_var validator
	// setting validator

	if (g_var.argc > 1)
	{
		ft_putendl_fd("JIP-shell: Do not support this mode", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	
}

void	check_EOF(char *str)
{
	if (str == NULL)
	{
		ft_putendl_fd("\x1b[1A\033[12Cexit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}
