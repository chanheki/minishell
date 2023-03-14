#include "../../include/parse.h"

void	clear_nodes(t_ASTnode **root)
{
	if (*root == NULL)
		return ;
	clear_nodes(&(*root)->left);
	clear_nodes(&(*root)->right);
	free((*root)->token);
	free(*root);
}
