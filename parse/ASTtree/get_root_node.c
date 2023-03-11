#include "../../include/parse.h"

t_ASTnode	*get_root_node(t_ASTnode *node)
{
	t_ASTnode	*root_node;

	root_node = NULL;
	while (node->parent)
	{
		root_node = node;
		node = node->parent;
	}
	return (root_node);
}
