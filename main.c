
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./include/minishell.h"

t_global	g_var;

static void	hosting_loop(void)
{
	char		*str;
	t_ASTnode	*cmdTree;

	while (1)
	{
		str = readline(PROMPT);
		check_EOF(str);
		add_history(str);
		cmdTree = parse_command_line(str);
		if (cmdTree != NULL)
			execute(cmdTree);
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
