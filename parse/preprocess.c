#include "../include/minishell.h"

char	**preprocess_line(char *line)
{
	char		**split_line;
	t_ASTnode	*root;

	split_line = split_command_line(line);
	root = tokenize_command_line(split_line);
	free_strings(split_line);
	interpret_env_var(root);
	interpret_wildcard(root);
	return (root);
}
