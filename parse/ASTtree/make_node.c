#include "../../include/minishell.h"

/*
 * Description: 괄호에 해당하는 노드를 만들어서 반환한다.
 *              1. 괄호 내 마지막 토큰을 찾는다.
 *               1.1. 만약 괄호 내 마지막 토큰이 없다면, OK를 반환한다.
 *              2. 괄호 토큰을 괄호 내 마지막 토큰의 다음 토큰(닫힌 괄호)으로 설정한다.
 *              3. 괄호 내 마지막 토큰의 다음 토큰을 NULL로 설정하고, 오직 (...)의 내용(토큰 리스트)만 남게 된다.
 *              4. 이후, (...)의 내용(토큰 리스트)을 AST Tree로 파싱하여 새로운 트리를 생성한다.
 *              5. 괄호 내 마지막 토큰의 다음 토큰을 닫힌 괄호 토큰으로 할당함으로써 원래대로 복구한다.
 *              6. 만약 (...)의 내용(토큰 리스트)을 AST Tree로 파싱할 때 오류가 발생한다면, NULL을 반환한다.
 *              7. 새로운 트리를 루트로 지정한다.
 *               7.1. 만약 현재 토큰이 연산자라면, 새로운 트리를 루트의 오른쪽 자식으로 지정한다.
 * Param.   #1: 트리의 루트 노드
 * Param.   #2: 현재 토큰
 * Return     : SUCCESS          : 노드 생성에 문제가 없음
 *              ERROR: 노드 생성 시, 메모리 할당에서 실패
 *              FAIL       : 노드 생성에 문제가 있음
 */
int	make_parenthesis_node(t_ASTnode **ast_tree, t_token **current)
{
	t_ASTnode	*new_tree;
	t_token		*last_token;
	t_token		*parent_token;

	last_token = get_last_token_in_parenthesis(current);
	if (!last_token)
		return (SUCCESS);
	parent_token = last_token->next;
	last_token->next = NULL;
	new_tree = make_ast_tree(&(*current)->next);
	last_token->next = parent_token;
	if (!new_tree)
		return (FAIL);
	if (*ast_tree && is_operator(*current))
		add_node_to_direction(ast_tree, new_tree, RIGHT);
	else
		*ast_tree = new_tree;
	*current = parent_token;
	return (SUCCESS);
}

/*
 * Description: 연산자에 해당하는 노드를 만들어서 반환한다.
 *              1. 새로운 노드를 생성한다.
 *              2. 연산자 우선 순위가 더 높은 노드를 부모 노드로 가져온다.
 *              3. 부모 노드의 유무에 따라 새로운 노드를 AST Tree에 추가한다.
 *               3.1. 부모 노드가 있다면(= 현재 노드보다 더 우선 순위가 높은 노드가 있다면),
 *                    새로운 노드의 왼쪽 자식으로 부모 노드의 오른쪽 자식을 추가하고,
 *                    부모 노드의 오른쪽 자식으로 새로운 노드를 추가한다.
 *               3.2. 부모 노드가 없다면(= 현재 노드가 우선 순위가 제일 높은 노드라면),
 *                    새로운 노드의 왼쪽 자식으로 AST Tree의 루트 노드를 추가한다.
 *              4. 이후 AST Tree의 루트 노드를 새로운 노드로 지정한다.
 * Param.   #1: 트리의 루트 노드
 * Param.   #2: 현재 토큰
 * Return     : SUCCESS          : 노드 생성에 문제가 없음
 *              ERROR: 노드 생성 시, 메모리 할당에서 실패
 *              FAIL       : 노드 생성에 문제가 있음
 */
int	make_operator_node(t_ASTnode **ast_tree, t_token *current)
{
	t_ASTnode	*new_node;
	t_ASTnode	*parent_node;

	new_node = create_new_node(current);
	if (!new_node)
		return (FAIL);
	parent_node = get_parent_node(*ast_tree, current);
	if (parent_node)
	{
		add_node_to_direction(&new_node, parent_node->right, LEFT);
		add_node_to_direction(&parent_node, new_node, RIGHT);
	}
	else
		add_node_to_direction(&new_node, get_root_node(*ast_tree), LEFT);
	*ast_tree = new_node;
	return (SUCCESS);
}

/*
 * Description: 리다이렉션에 해당하는 노드를 만들어서 반환한다.
 *              1. 현재 토큰의 다음 토큰이 없다면, 에러를 반환한다.
 *              2. 새로운 노드를 생성한다.
 *              3. 현재 토큰의 다음 토큰을 파일과 관련된 노드라 간주하여 파일 노드를 생성한다.
 *              4. AST Tree의 루트를 최우측 노드로 이동시킨다.
 *              5. AST Tree의 최우측 노드의 오른쪽 자식으로 새로운 노드를 추가한다.
 *              6. 새로운 노드의 왼쪽 자식으로 파일 노드를 추가한다.
 * Param.   #1: 트리의 루트 노드
 * Param.   #2: 현재 토큰
 * Return     : SUCCESS          : 노드 생성에 문제가 없음
 *              ERROR: 노드 생성 시, 메모리 할당에서 실패
 *              FAIL       : 노드 생성에 문제가 있음
 */
int	make_redirection_node(t_ASTnode **ast_tree, t_token **current)
{
	t_ASTnode	*new_node;
	t_ASTnode	*file_node;

	if (!(*current)->next)
		return (FAIL);
	new_node = create_new_node(*current);
	if (!new_node)
		return (ERROR);
	(*current) = (*current)->next;
	file_node = create_new_node(*current);
	if (!file_node)
		return (ERROR);
	while ((*ast_tree)->right)
		(*ast_tree) = (*ast_tree)->right;
	add_node_to_direction(ast_tree, new_node, RIGHT);
	add_node_to_direction(&new_node, file_node, LEFT);
	return (SUCCESS);
}

/*
 * Description: 일반 노드를 만들어서 반환한다.
 *              1. 새로운 노드를 생성한다.
 *               1.1. 루트 노드에 토큰이 없다면, 루트 노드에 토큰을 추가한다.
 *              2. 루트 노드를 AST Tree의 최좌측 노드로 지정한다.
 *              3. AST Tree의 최좌측 노드의 왼쪽 자식으로 새로운 노드를 추가한다.
 * Param.   #1: 트리의 루트 노드
 * Param.   #2: 현재 토큰
 * Return     : SUCCESS          : 노드 생성에 문제가 없음
 *              ERROR: 노드 생성 시, 메모리 할당에서 실패
 *              FAIL       : 노드 생성에 문제가 있음
 */
int	make_normal_node(t_ASTnode **ast_tree, t_token **current)
{
	t_ASTnode	*new_node;

	if (!(*ast_tree)->token)
	{
		(*ast_tree)->token = *current;
		return (SUCCESS);
	}
	new_node = create_new_node(*current);
	if (!new_node)
		return (ERROR);
	while ((*ast_tree)->left)
		(*ast_tree) = (*ast_tree)->left;
	add_node_to_direction(ast_tree, new_node, LEFT);
	return (SUCCESS);
}

/*
 * Description: 명령어에 해당하는 노드를 만들어서 반환한다.
 *              1. 만약, 루트 노드가 없거나, 루트 노드의 토큰이 연산자라면 새로운 노드를 생성하고
 *                 새로운 노드를 루트 노드의 오른쪽에 추가하여 루트 노드를 새로운 노드로 지정한다.
 *              2. 만약 토큰이 리다이렉션이라면, 리다이렉션 노드를 생성하여 반환한다.
 *              3. 만약 토큰이 일반 노드라면, 일반 노드를 생성하여 반환한다.
 * Param.   #1: 트리의 루트 노드
 * Param.   #2: 현재 토큰
 * Return     : SUCCESS          : 노드 생성에 문제가 없음
 *              ERROR: 노드 생성 시, 메모리 할당에서 실패
 *              FAIL       : 노드 생성에 문제가 있음
 */
int	make_command_node(t_ASTnode **ast_tree, t_token **current)
{
	t_ASTnode	*new_node;

	if (!(*ast_tree) || is_operator((*ast_tree)->token))
	{
		new_node = create_new_node(NULL);
		if (!new_node)
			return (ERROR);
		add_node_to_direction(ast_tree, new_node, RIGHT);
		*ast_tree = new_node;
	}
	if ((*current)->type == REDIRECT_IN || (*current)->type == REDIRECT_OUT
		|| (*current)->type == DREDIRECT_IN
		|| (*current)->type == DREDIRECT_OUT)
		return (make_redirection_node(ast_tree, current));
	else if ((*current)->type == NORMAL)
		return (make_normal_node(ast_tree, current));
	return (SUCCESS);
}
