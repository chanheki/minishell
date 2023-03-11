#include "../include/parse.h"

t_token	*parse_command_line(char *line)
{
	char		**trimmed_line;
	char		**preprocessed_line;
	t_token		*token;
	t_ASTnode	*ast_tree;

	trimmed_line = ft_strtrim(line, " ");
	if (!trimmed_line)
		return (NULL);
	token = tokenize_line(trimmed_line);
	free(trimmed_line);
	if (token && is_valid_syntax(token))
		return (token);
	else
		return (NULL);
}
