#include "../../include/parse.h"

void	add_node_to_direction(t_ASTnode **node, t_ASTnode *new_node, int direction)
{
	if (*node && direction == LEFT)
		(*node)->left = new_node;
	else if (*node && direction == RIGHT)
		(*node)->right = new_node;
	if (new_node)
		new_node->parent = *node;
}
