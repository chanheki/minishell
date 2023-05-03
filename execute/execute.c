#include "../include/minishell.h"

t_global	g_var;

char	*find_path(char *cmd)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(g_var.envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(g_var.envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	_execute(char *argv)
{
	char	**cmd;
	char	*path;
	int		i;

	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0]);
	i = -1;
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		perror("path error");
	}
	if (execve(path, cmd, g_var.envp) == -1)
		perror("execve error");
}

void	execute_(char *str)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		perror("pipe error");
	pid = fork();
	if (pid < 0)
		perror("fork error");
	if (pid == 0)
		_execute(str);
	if (wait(&pid) == -1)
		perror("waitpid error");
}

void	execute_validator_handler(char *cmd, t_exitcode errcode)
{
	if (errcode == EXIT_COMMAND_NOT_FOUND)
	{
		ft_putstr_fd("jip: ", STDOUT_FILENO);
		ft_putstr_fd(cmd, STDOUT_FILENO);
		ft_putstr_fd(": command not found \n", STDERR_FILENO);
	}
	g_var.exit_status = EXIT_COMMAND_NOT_FOUND;

}

static bool	is_cmd(t_ASTnode *node)
{
	t_token	*token;

	token = (t_token *)node->token;
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

static pid_t	*empty_pid_list(t_ASTnode **cmd_list)
{
	pid_t	*pid_list;
	int		i;

	i = 0;
	while (cmd_list[i])
		i++;
	pid_list = (pid_t *)ft_calloc(i + 1, sizeof(pid_t));
	return (pid_list);
}

static int	wait_proc(pid_t *pid_list)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (pid_list[i])
	{
		waitpid(pid_list[i], &status, 0);
		if (0 < status && status < 256)
			status = (128 + status) * 256;
		i++;
	}
	return (status / 256);
}

static t_error	execute_child(t_ASTnode *root)
{
	t_ASTnode	**cmd_list;
	pid_t		*pid_list;

	cmd_list = make_cmd_list(root);
	if (!cmd_list)
		return (ERROR);
	pid_list = empty_pid_list(cmd_list);
	if (!pid_list
		// || execute_all_heredoc(cmd_list) != SUCCESS
		|| create_childs(cmd_list, pid_list) == ERROR)
	{
		free(pid_list);
		free(cmd_list);
		return (ERROR);
	}
	g_var.exit_status = wait_proc(pid_list);
	free(pid_list);
	free(cmd_list);
	return (SUCCESS);
}

static void	execute_tree(t_ASTnode *cmd_tree)
{
	t_error	errno;

	if (check_builtin(cmd_tree->token->value))
		errno = execute_parent(cmd_tree);
	else
		errno = execute_child(cmd_tree);
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_var.new_term));
	signal(SIGINT, sigint_prompt_handler);
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