/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parent_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:53:19 by yena              #+#    #+#             */
/*   Updated: 2023/05/10 20:53:20 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ASTnode	*get_parent_node(t_ASTnode *node, t_token *current)
{
	t_ASTnode	*parent_node;

	parent_node = node;
	while (parent_node)
	{
		if (parent_node->token->type > current->type)
			return (parent_node);
		parent_node = parent_node->parent;
	}
	return (parent_node);
}
