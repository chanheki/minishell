#include "../include/minishell.h"

static bool	is_heredoc(t_ASTnode *node)
{
	return (check_token_type(node, DREDIRECT_IN));
}

t_error	execute_all_heredoc(t_ASTnode **cmd_list)
{
	int			i;
	t_ASTnode	*node;

	i = -1;
	if (signal(SIGINT, sigint_heredoc) == SIG_ERR)
		return (ERROR);
	while (cmd_list[++i])
	{
		node = cmd_list[i];
		while (node)
		{
			if (is_heredoc && execute_heredoc(node) == ERROR)
				return (ERROR);
			if (g_var.is_signal)
			{
				g_var.is_signal = 0;
				signal(SIGINT, sigint_prompt);
				return (FAIL);
			}
			node = node->right;
		}
	}
	if (signal(SIGINT, sigint_prompt) == SIG_ERR)
		return (ERROR);
	return (SUCCESS);
}
