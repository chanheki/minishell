
#include "../include/minishell.h"

extern t_global	g_var;

t_error	initialize_setting(t_global	g_var)
{
	// Setting
	return (SUCCESS);
}

void initialize_global_variable(int argc, char **argv, char **env)
{
	g_var.argv = argv;
	g_var.argc = argc;
	g_var.envp = env;
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