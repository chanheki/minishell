/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:53:30 by yena              #+#    #+#             */
/*   Updated: 2023/05/10 20:53:31 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Description: 토큰을 순회하며, 토큰의 타입에 따라 AST Tree를 만든다.
 *              트리를 생성하는 동안, 노드 생성에 실패한다면 트리를 삭제하고 NULL을 반환한다.
 *              1. 토큰이 괄호라면, 괄호에 해당하는 노드를 만든다.
 *              2. 토큰이 연산자라면, 연산자에 해당하는 노드를 만든다.
 *              3. 그 밖의 토큰이라면, 명령어에 해당하는 노드를 만든다.
 * Param.   #1: 토큰 리스트의 주소
 * Return     : AST Tree의 루트 노드
 */
t_ASTnode	*make_ast_tree(t_token **token)
{
	t_token		*current;
	t_ASTnode	*ast_tree;
	int			status;

	current = *token;
	ast_tree = NULL;
	while (current)
	{
		if (current->type == PARENTHESIS_OPEN
			|| current->type == PARENTHESIS_CLOSE)
			status = make_parenthesis_node(&ast_tree, &current);
		else if (is_operator(current))
			status = make_operator_node(&ast_tree, current);
		else
			status = make_command_node(&ast_tree, &current);
		if (status == FAIL || status == ERROR)
		{
			clear_nodes(&ast_tree);
			return (NULL);
		}
		current = current->next;
	}
	return (get_root_node(ast_tree));
}
