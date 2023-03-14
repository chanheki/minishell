#include "../../include/parse.h"

t_ASTnode	*make_ast_tree(t_token **token)
{
	t_token		*current;
	t_ASTnode	*ast_tree;
	int			status;

	current = *token;
	ast_tree = NULL;
	while (current)
	{
		if (current->type == PARENTHESIS_OPEN
			|| current->type == PARENTHESIS_CLOSE)
			status = make_parenthesis_node(&ast_tree, &current);
		else if (is_operator(current))
			status = make_operator_node(&ast_tree, current);
		else
			status = make_command_node(&ast_tree, &current);
		if (status == ERROR || status == MEMORY_ERROR)
		{
			clear_nodes(&ast_tree);
			return (NULL);
		}
		current = current->next;
	}
	return (get_root_node(ast_tree));
}
