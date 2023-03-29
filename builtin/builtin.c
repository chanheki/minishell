#include "../include/minishell.h"

t_global	g_var;

int	check_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") 
	|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "env") 
	|| !ft_strcmp(cmd, "unse") || !ft_strcmp(cmd, "export") 
	|| !ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

int	exec_builtin(char *path, char **argv)
{
	if (!ft_strcmp(path, "cd"))
		return(ft_cd(argv));
	else if (!ft_strcmp(path, "echo"))
		return(ft_echo(argv));
	else if (!ft_strcmp(path, "env"))
		return(ft_env());
	else if (!ft_strcmp(path, "exit"))
		return(ft_exit());
	else if (!ft_strcmp(path, "export"))
		return(ft_export());
	else if (!ft_strcmp(path, "pwd"))
		return(ft_pwd());
	else if (!ft_strcmp(path, "unset"))
		return(ft_unset());
	ft_putendl_fd("exec_builtin : invalid path", STDERR_FILENO);
	return (-1);
}

static t_error	set_redirection(int fd[2], t_ASTnode **cmd_list, char **cmd_argv)
{
	// if (fd[0] < 0 || fd[1] < 0 || execute_all_heredoc(cmd_list) != SUCCESS
	// 	|| apply_redirections(cmd_list[0]) == ERROR)
	if (fd[0] < 0 || fd[1] < 0)
	{
		close(fd[0]);
		close(fd[1]);
		ft_split_free(cmd_argv);
		free(cmd_list);
		return (ERROR);
	}
	return (SUCCESS);
}

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
	int		cmd_count;

	cmd_count = count_cmd_node(root);
	cmd_list = (t_ASTnode **)ft_calloc(cmd_count + 1, sizeof(t_ASTnode *));
	if (!cmd_list)
		return (NULL);
	cmd_preorder(root, cmd_list, cmd_count - 1);
	return (cmd_list);
}

t_error	ft_dup2(int fd1, int fd2)
{
	if (close(fd2) == -1)
		return (ERROR);
	if (dup2(fd1, fd2) == -1)
		return (ERROR);
	if (close(fd1) == -1)
		return (ERROR);
	return (SUCCESS);
}

t_error	execute_builtin(t_ASTnode *node)
{
	t_ASTnode	**cmd_list;
	char		**cmd_argv;
	char		*path;
	int			fd[2];

	path = node->token->value;
	cmd_argv = make_argv(node);
	if (!cmd_argv)
		return (ERROR);
	cmd_list = make_cmd_list(node);
	if (!cmd_list)
	{
		ft_split_free(cmd_argv);
		return (ERROR);
	}
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (set_redirection(fd, cmd_list, cmd_argv) == ERROR)
		return (ERROR);
	g_var.exit_status = exec_builtin(path, cmd_argv);
	ft_dup2(fd[0], STDIN_FILENO);
	ft_dup2(fd[1], STDOUT_FILENO);
	ft_split_free(cmd_argv);
	free(cmd_list);
	return (SUCCESS);
}
