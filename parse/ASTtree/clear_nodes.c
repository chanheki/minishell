#include "../../include/parse.h"

/*
 * Description: AST Tree 내의 모든 노드를 삭제한다.
 * Param.   #1: AST Tree의 루트 노드
 * Return     : 없음
 */
void	clear_nodes(t_ASTnode **root)
{
	if (*root == NULL)
		return ;
	clear_nodes(&(*root)->left);
	clear_nodes(&(*root)->right);
	free((*root)->token);
	free(*root);
}
