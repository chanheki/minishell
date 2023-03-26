
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./include/minishell.h"

t_global	g_var;

static void	hosting_loop(void)
{
	char		*str;
	t_ASTnode	*base;

	while (1)
	{
		str = readline(PROMPT);
		check_EOF(str);
		add_history(str);
		base = parse_command_line(str);

		// TODO: parsing line
		// if (!parsing) - exception
		if (base == NULL) {}

		// TODO: exe line
		execute(str);

		// TODO: buffer clear
		// clear(base)
		free(str);
	}
}

int	main(int argc, char **argv, char **env)
{
	initialize_setting();
	initialize_global_variable(argc, argv, env);
	validator();
	hosting_loop();
	return (g_var.exit_status);
}
