#include "../include/parse.h"

t_ASTnode	*parse_command_line(char *line)
{
	char		**trimmed_line;
	t_token		*token;
	t_ASTnode	*ast_tree;

	trimmed_line = ft_strtrim(line, " ");
	if (!trimmed_line)
		return (NULL);
	token = tokenize_line(trimmed_line);
	free(trimmed_line);
	if (!token)
		return (NULL);
	if (!is_valid_syntax(token))
	{
		free_token_list(&token);
		return (NULL);
	}
	ast_tree = make_ast_tree(&token);
	if (!ast_tree)
		return (NULL);
	return (ast_tree);
}
