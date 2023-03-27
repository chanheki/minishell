#include "../../include/minishell.h"

t_ASTnode	*get_parent_node(t_ASTnode *node, t_token *current)
{
	t_ASTnode	*parent_node;

	parent_node = node;
	while (parent_node)
	{
		if (parent_node->token->type > current->type)
			return (parent_node);
		parent_node = parent_node->parent;
	}
	return (parent_node);
}
