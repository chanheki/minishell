#include "../../include/parse.h"

int make_parenthesis_node(t_ASTnode **ast_tree, t_token **current)
{
	t_ASTnode	*new_tree;
	t_token		*last_token;
	t_token 	*parent_token;

	last_token = get_tail_token(current);
	if (!last_token)
		return (MEMORY_ERROR);
	parent_token = last_token->next;
	last_token->next = NULL;
	new_tree = make_ast_tree(&(*current)->next);
	last_token->next = parent_token;
	if (!new_tree)
		return (ERROR);
	if (*ast_tree
		&& ((*current)->type == AMPERSAND || (*current)->type == PIPE))
		add_node_to_direction(ast_tree, new_tree, RIGHT);
	else
		*ast_tree = new_tree;
	*current = parent_token;
	return (OK);
}

int make_operator_node(t_ASTnode **ast_tree, t_token **current)
{
	t_ASTnode	*new_node;
	t_ASTnode	*parent_node;

	new_node = create_new_node(*current, (*current)->type);
	if (!new_node)
		return (MEMORY_ERROR);
	parent_node = get_parent_node(*ast_tree, *current);
	if (parent_node)
	{
		add_node_to_direction(&new_node, parent_node->right, LEFT);
		add_node_to_direction(&parent_node, new_node, RIGHT);
	}
	else
	{
		parent_node = get_root_node(*ast_tree);
		add_node_to_direction(&new_node, parent_node, LEFT);
	}
	*ast_tree = new_node;
	return (OK);
}

int make_redirection_node(t_ASTnode **ast_tree, t_token **current)
{
	t_ASTnode	*right_node;
	t_ASTnode	*new_node;
	t_ASTnode	*file_node;

	if (!(*current)->next)
		return (ERROR);
	new_node = create_new_node(*current, (*current)->type);
	if (!new_node)
		return (MEMORY_ERROR);
	(*current) = (*current)->next;
	file_node = create_new_node(*current, (*current)->type);
	if (!file_node)
		return (MEMORY_ERROR);
	right_node = *ast_tree;
	while (right_node->right)
		right_node = right_node->right;
	add_node_to_direction(&right_node, new_node, RIGHT);
	add_node_to_direction(&new_node, file_node, LEFT);
	return (OK);
}

int make_normal_node(t_ASTnode **ast_tree, t_token **current)
{
	t_ASTnode	*new_node;
	t_ASTnode	*left_node;

	if (!(*ast_tree)->token)
	{
		(*ast_tree)->token = *current;
		(*ast_tree)->type = (*current)->type;
		(*ast_tree)->left = NULL;
		(*ast_tree)->right = NULL;
		(*ast_tree)->parent = NULL;
		return (OK);
	}
	new_node = create_new_node(*current, (*current)->type);
	if (!new_node)
		return (MEMORY_ERROR);
	left_node = *ast_tree;
	while (left_node->left)
		left_node = left_node->left;
	add_node_to_direction(&left_node, new_node, LEFT);
	return (OK);
}

int	make_command_node(t_ASTnode **ast_tree, t_token **current)
{
	t_ASTnode	*new_node;

	if (!(*ast_tree)
		|| ((*current)->type == AMPERSAND || (*current)->type == PIPE))
	{
		new_node = create_new_node(*current, (*current)->type);
		if (!new_node)
			return (MEMORY_ERROR);
		add_node_to_direction(ast_tree, new_node, RIGHT);
		*ast_tree = new_node;
	}
	if ((*current)->type == REDIRECT_IN || (*current)->type == REDIRECT_OUT
		|| (*current)->type == DREDIRECT_IN || (*current)->type == DREDIRECT_OUT)
		return (make_redirection_node(ast_tree, current));
	else if ((*current)->type == NORMAL)
		return (make_normal_node(ast_tree, current));
	return (OK);
}
