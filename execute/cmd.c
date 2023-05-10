#include "../include/minishell.h"

/*
 * Description: 해당 node가 cmd인지 확인한다.
 *            : NORMAL token type은 cmd로 간주한다.
 * Param.   #1: node
 * Return     : true = cmd다.
 *            : false = cmd가 아니다.
 */
static bool	is_cmd(t_ASTnode *node)
{
	t_token	*token;

	token = node->token;
	if (token->type == NORMAL)
		return (true);
	return (false);
}

/*
 * Description: cmd node의 갯수를 센다. (node)
 *            : 해당 node에 달린 모든 cmd 노드의 갯수를 센다.
 * Param.   #1: node
 * Return     : int count
 */
static int	cmd_node_count(t_ASTnode *node)
{
	int	count;

	count = 0;
	if (is_cmd(node))
		return (1);
	count += cmd_node_count(node->left);
	count += cmd_node_count(node->right);
	return (count);
}

/*
 * Description: cmd를 전위 순회한다.
 *            : 전위 순회를 재귀적으로 하며 해당 노드들을 idx 순으로 cmd list에 담는다.
 * Param.   #1: node
 * Return     : int count
 */
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

/*
 * Description: cmd list를 만든다.(cmd)
 *            : 해당 cmd에 달린 모든 노드들을 전위 순회하며 추가한다.
 * Param.   #1: cmd
 * Return     : **argv (해당 cmd의 옵션값들)
 */
t_ASTnode	**generate_cmd_list(t_ASTnode *root)
{
	t_ASTnode	**cmd_list;
	int			cmd_count;

	cmd_count = cmd_node_count(root);
	cmd_list = (t_ASTnode **)ft_calloc(cmd_count + 1, sizeof(t_ASTnode *));
	if (!cmd_list)
		return (NULL);
	cmd_preorder(root, cmd_list, cmd_count - 1);
	return (cmd_list);
}
