#include "../include/minishell.h"

/*
 * Description: excute(root_node)
 *            : root node부터 재귀적으로 token 타입을 체크하여 우선순위를 정한 후
 *            : 우선순위 토큰타입이 아닌 경우 execute tree를 만든다.
 * Param.   #1: parsing tree의 root node
 */
static void	execute_tree(t_ASTnode *cmd)
{
	t_error	errno;

	if (check_builtin(cmd->token->value))
		errno = execute_parent(cmd);
	else
		errno = execute_child(cmd);
	set_signal();
	set_terminal_attribute();
	if (errno)
		g_var.exit_status = 1;
}

/*
 * Description: excute(root_node)
 *            : root node부터 재귀적으로 token 타입을 체크하여 우선순위를 정한 후
 *            : 우선순위 토큰타입이 아닌 경우 execute tree를 만든다.
 * Param.   #1: parsing tree의 root node
 */
void	execute(t_ASTnode *node)
{
	t_token		*token;

	if (!node)
		return ;
	token = node->token;
	if (!check_token_type_operator(token))
	{
		execute_tree(node);
		return ;
	}
	execute(node->left);
	if (ft_strcmp(token->value, "&&") == 0 && g_var.exit_status == 0)
		execute(node->right);
	else if (ft_strcmp(token->value, "||") == 0 && g_var.exit_status != 0)
		execute(node->right);
}
