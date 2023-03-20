#include "../../include/parse.h"

t_ASTnode	*create_new_node(t_token *token)
{
	t_ASTnode	*new_node;

	new_node = (t_ASTnode *)malloc(sizeof(t_ASTnode));
	if (!new_node)
		return (0);
	new_node->token = token;
	new_node->parent = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}
