#include "../include/minishell.h"

static void	run_code(char *str)
{
	t_ASTnode	*root;

	root = parse_command_line(str);
	if (!root)
		return ;
	execute(root);
	clear_nodes(&root);
}

static t_error	make_dir(void)
{
	char	*path;

	path = ft_strjoin("mkdir -p ", g_var.tmp_path);
	if (!path)
		return (ERROR);
	run_code(path);
	free(path);
	return (SUCCESS);
}

void	set_tmp(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		exit(1);
	g_var.tmp_path = ft_strjoin(path, "/tmp");
	free(path);
	if (!g_var.tmp_path || make_dir() == ERROR)
		exit(1);
}

static bool	is_heredoc(t_token *token)
{
	return (check_token_type(token, DREDIRECT_IN));
}

t_error	heredoc(t_ASTnode **cmd_list)
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
			if (is_heredoc(node->token) && execute_heredoc(node) == ERROR)
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
