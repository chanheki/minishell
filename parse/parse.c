#include "../include/parse.h"

char	**parse_command_line(char *line)
{
	char		**trimmed_line;
	char		**preprocessed_line;
	t_token		*token;
	t_ASTnode	*ast_tree;

	trimmed_line = ft_strtrim(line, " ");
	if (!trimmed_line)
		return ;
	token = tokenize_line(trimmed_line);
	free(trimmed_line);
	if (has_empty_value_in_token(token))
		// TODO => implements has_empty_value_in_token()
	if (token && is_valid_syntax(token))
		//TODO => implements is_valid_syntax()
	else
		return (NULL);
}
