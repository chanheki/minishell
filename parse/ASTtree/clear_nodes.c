/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:53:08 by yena              #+#    #+#             */
/*   Updated: 2023/05/10 20:53:09 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	free((*root)->token->value);
	(*root)->token->value = NULL;
	free((*root)->token);
	(*root)->token = NULL;
	(*root)->left = NULL;
	(*root)->right = NULL;
	(*root)->parent = NULL;
	free(*root);
	*root = NULL;
}
