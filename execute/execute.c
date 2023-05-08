#include "../include/minishell.h"

static void	execute_tree(t_ASTnode *cmd_tree)
{
	t_error	errno;

	if (check_builtin(cmd_tree->token->value))
		errno = execute_parent(cmd_tree);
	else
		errno = execute_child(cmd_tree);
	set_signal();
	set_terminal_attribute();
	if (errno)
		g_var.exit_status = 1;
}

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
	{
		printf("%s\n", token->value);
		execute(node->right);
	}
	else if (ft_strcmp(token->value, "||") == 0 && g_var.exit_status != 0)
	{
		printf("%s\n", token->value);
		execute(node->right);
	}
}
