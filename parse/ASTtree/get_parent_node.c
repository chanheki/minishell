#include "../../include/parse.h"

t_ASTnode	*get_parent_node(t_ASTnode *node, t_token *current)
{
	t_ASTnode	*parent_node;

	parent_node = NULL;
	while (node)
	{
		if (node->token->type > current->type)
			return (node);
		node = node->parent;
	}
	return (parent_node);
}
