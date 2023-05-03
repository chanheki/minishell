
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./include/minishell.h"

t_global	g_var;

static void	minishell_will_terminate()
{
	// free & clear setting
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_var.old_term));
}

static void	hosting_loop(void)
{
	char		*str;
	t_ASTnode	*root_node;

	while (1)
	{
		str = readline(PROMPT);
		check_eof(str);
		add_history(str);
		root_node = parse_command_line(str);
		if (!root_node)
			continue ;
		execute(root_node);
		clear_nodes(&root_node);
		free(str);
	}
}

int	main(int argc, char **argv, char **env)
{
	initialize_global_variable(argc, argv, env);
	initialize_setting();
	validator();
	hosting_loop();
	minishell_will_terminate();
	return (g_var.exit_status);
}
