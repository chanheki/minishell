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
void exec_cmd_list(t_cmd_list *exec_cmd_list)
{
	(void)(exec_cmd_list);
}

static void	execute_tree(t_ASTnode *cmd_tree)
{
	t_error	errno;

	if (check_builtin(cmd_tree->token->value))
		errno = execute_builtin(cmd_tree);
	// else
	// 	errno = execute_child(cmd_tree);
	// tcsetattr(STDIN_FILENO, TCSANOW, &(g_var.new_term));
	// signal(SIGINT, sigint_handler_prompt);
	if (errno)
		g_var.exit_status = 1;
}

void	execute(t_ASTnode *cmd_tree)
{
	t_token		*token;

	token = cmd_tree->token;
	if (!check_token_type_operator(token))
	{
		execute_tree(cmd_tree);
		return ;
	}
	execute(cmd_tree->left);
	if (ft_strcmp(token->value, "&&") == 0 && g_var.exit_status == 0)
	{
		printf("%s\n", token->value);
		execute(cmd_tree->right);
	}
	else if (ft_strcmp(token->value, "||") == 0 && g_var.exit_status != 0)
	{
		printf("%s\n", token->value);
		execute(cmd_tree->right);
	}
}