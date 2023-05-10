/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:53:13 by yena              #+#    #+#             */
/*   Updated: 2023/05/10 20:53:14 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
