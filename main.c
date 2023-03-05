
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./include/minishell.h"

t_global	g_var;

static void	hosting_loop(void)
{
	char		*str;
	// t_ASTnode	*base;

	// base = NULL;
	while (1)
	{
		str = readline(PROMPT);
		if (str == NULL)
		{
			ft_putendl_fd("\x1b[1A\033[12Cexit", STDOUT_FILENO);
			break ;
		}
		if (ft_strcmp(str, "") == 0)
		{
			free(str);
			continue ;
		}
		// TODO: history add
		// add_history(str);

		// TODO: parsing line
		// if (!parsing) - exception

		// TODO: exe line
		execute(str);

		// TODO: buffer clear
		// clear(base)
		free(str);
	}
}

void initialize_global_variable(char **env)
{
	g_var.envp = env;
}

void validator(argc)
{	
	if (argc > 1)
	{
		ft_putendl_fd("JIP-shell: \
Do not support this mode\
		", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **env)
{
	(void) argv;
	ft_putstr_fd(MINISHELLHEADER, 2);
	initialize_global_variable(env);
	validator(argc);
	hosting_loop();
	return 0;
}