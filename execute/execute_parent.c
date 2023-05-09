#include "../include/minishell.h"

static t_error	set_ready_to_excute(
	int fd[2], t_ASTnode **cmd_list, char **cmd_argv)
{
	fd[FD_READ] = dup(STDIN_FILENO);
	fd[FD_WRITE] = dup(STDOUT_FILENO);
	if (fd[FD_READ] < 0 || fd[FD_WRITE] < 0
		|| heredoc(cmd_list) != SUCCESS
		|| redirect(cmd_list[0]) == ERROR)
	{
		close(fd[FD_READ]);
		close(fd[FD_WRITE]);
		ft_split_free(cmd_argv);
		free(cmd_list);
		return (ERROR);
	}
	return (SUCCESS);
}

static void	execute_will_terminate(
	int fd[2], t_ASTnode **cmd_list, char **cmd_argv)
{
	ft_dup2(fd[FD_READ], STDIN_FILENO);
	ft_dup2(fd[FD_WRITE], STDOUT_FILENO);
	ft_split_free(cmd_argv);
	free(cmd_list);
}

t_error	execute_parent(t_ASTnode *node)
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
	if (set_ready_to_excute(fd, cmd_list, cmd_argv) == ERROR)
		return (ERROR);
	g_var.exit_status = execute_builtin(path, cmd_argv, P_PARENT);
	execute_will_terminate(fd, cmd_list, cmd_argv);
	return (SUCCESS);
}
