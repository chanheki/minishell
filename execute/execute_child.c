
#include "../include/minishell.h"

extern t_global	g_var;

static void	child_execve(t_ASTnode *node, char *path, char **argv)
{
	char	*builtin;

	builtin = node->token->value;
	if (check_builtin(builtin) == false && !path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(argv[0], STDERR_FILENO);
		if (ft_strcmp(argv[0], "") != 0 && is_directory(argv[0]))
		{
			ft_putendl_fd(": is a directory", STDERR_FILENO);
			exit(126);
		}
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit(127);
	}
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR
		|| signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(1);
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_var.old_term));
	if (check_builtin(builtin) == true)
		exit(exec_builtin(path, argv));
	execve(path, argv, g_var.envp);
	exit(0);
}

static t_error	child_execute(t_ASTnode *cmd_node)
{
	char	**cmd_argv;
	char	*path;

	cmd_argv = make_argv(cmd_node);
	if (!cmd_argv)
		return (ERROR);
	if (redirect(cmd_node) == ERROR
		|| make_cmd_path(cmd_argv[0], &path, g_var.envp) == ERROR)
	{
		ft_split_free(cmd_argv);
		return (ERROR);
	}
	child_execve(cmd_node, path, cmd_argv);
	return (SUCCESS);
}

static pid_t	fork_child(t_ASTnode *cmd_node, int *before_fd)
{
	int		fd[2];
	pid_t	child_pid;
	int		tmp;

	if (pipe(fd) == -1)
		return (0);
	tmp = *before_fd;
	*before_fd = fd[0];
	child_pid = fork();
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
	{
		if (close(fd[0]) == -1
			|| (tmp != STDIN_FILENO && ft_dup2(tmp, STDIN_FILENO) == ERROR)
			|| ft_dup2(fd[1], STDOUT_FILENO) == ERROR
			|| child_execute(cmd_node) == ERROR)
			exit(1);
	}
	if ((tmp != STDIN_FILENO && close(tmp) == -1)
		|| close(fd[1]) == -1)
		return (0);
	return (child_pid);
}

static pid_t	last_fork_child(t_ASTnode *cmd_node, int before_fd)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
	{
		if (before_fd != STDIN_FILENO
			&& ft_dup2(before_fd, STDIN_FILENO) == ERROR)
			exit(1);
		if (child_execute(cmd_node) == ERROR)
			exit(1);
	}
	if (before_fd != STDIN_FILENO && close(before_fd) == -1)
		return (0);
	return (child_pid);
}

t_error	create_childs(t_ASTnode **cmd_list, pid_t *pid_list)
{
	int	before_fd;
	int	i;

	before_fd = STDIN_FILENO;
	i = 0;
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		return (ERROR);
	while (cmd_list[i + 1])
	{
		pid_list[i] = fork_child(cmd_list[i], &before_fd);
		if (pid_list[i] == 0)
			return (ERROR);
		i++;
	}
	pid_list[i] = last_fork_child(cmd_list[i], before_fd);
	if (pid_list[i] == 0)
		return (ERROR);
	return (SUCCESS);
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

t_error	execute_child(t_ASTnode *root)
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
