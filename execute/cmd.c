#include "../include/minishell.h"

static bool	is_cmd(t_ASTnode *node)
{
	t_token	*token;

	token = node->token;
	if (token->type == NORMAL)
		return (true);
	return (false);
}

static int	count_cmd_node(t_ASTnode *node)
{
	int	cnt;

	cnt = 0;
	if (is_cmd(node))
		return (1);
	cnt += count_cmd_node(node->left);
	cnt += count_cmd_node(node->right);
	return (cnt);
}

static void	cmd_preorder(t_ASTnode *node, t_ASTnode **cmd_list, int idx)
{
	if (is_cmd(node))
	{
		cmd_list[idx] = node;
		return ;
	}
	cmd_preorder(node->left, cmd_list, idx - 1);
	cmd_preorder(node->right, cmd_list, idx);
}

t_ASTnode	**make_cmd_list(t_ASTnode *root)
{
	t_ASTnode	**cmd_list;
	int			cmd_count;

	cmd_count = count_cmd_node(root);
	cmd_list = (t_ASTnode **)ft_calloc(cmd_count + 1, sizeof(t_ASTnode *));
	if (!cmd_list)
		return (NULL);
	cmd_preorder(root, cmd_list, cmd_count - 1);
	return (cmd_list);
}
