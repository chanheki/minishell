#include "../../include/minishell.h"

/*
 * Description: 트리에 새로운 노드를 방향에 따라 추가한다.
 *              1. 방향이 왼쪽이라면, 루트 노드의 왼쪽 자식 노드로 추가하고,
 *                 새로운 노드의 부모 노드를 루트 노드로 지정한다.
 *              2. 방향이 오른쪽이라면, 루트 노드의 오른쪽 자식 노드로 추가하고,
 *                 새로운 노드의 부모 노드를 루트 노드로 지정한다.
 * Param.   #1: 트리의 루트 노드
 * Param.   #2: 추가할 노드
 * Param.   #3: 추가할 방향
 * Return     : 없음
 */
void	add_node_to_direction(t_ASTnode **node, t_ASTnode *new_node,
							int direction)
{
	if (*node && direction == LEFT)
		(*node)->left = new_node;
	else if (*node && direction == RIGHT)
		(*node)->right = new_node;
	if (new_node)
		new_node->parent = *node;
}
