#include "libft.h"

t_ASTnode	*create_new_node(void *value, int type)
{
	t_ASTnode	*new_node;

	new_node = (t_ASTnode *)malloc(sizeof(t_ASTnode));
	if (!new_node)
		return (0);
	new_node->type = type;
	new_node->value = value;
	new_node->parent = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}
