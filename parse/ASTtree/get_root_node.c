#include "../../include/parse.h"

/*
 * Description: AST Tree의 루트 노드를 반환한다.
 *              1. 현재 노드의 부모 노드가 존재하지 않을 때까지 노드를 순회한다.
 * Param.   #1: AST Tree의 현재 노드
 * Return     : AST Tree의 루트 노드
 */
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
