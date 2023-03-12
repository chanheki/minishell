#include "../../include/parse.h"

t_ASTnode	*get_root_node(t_ASTnode *node)
{
	t_ASTnode	*root_node;

	if (!node)
		return (NULL);
	root_node = node;
	while (root_node->parent)
		root_node = root_node->parent;
	return (root_node);
}
