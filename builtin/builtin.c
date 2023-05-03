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
	if (fd[0] < 0 || fd[1] < 0 
	// || execute_all_heredoc(cmd_list) != SUCCESS
		|| apply_redirections(cmd_list[0]) == ERROR)
	// if (fd[0] < 0 || fd[1] < 0)
	{
		close(fd[0]);
		close(fd[1]);
		ft_split_free(cmd_argv);
		free(cmd_list);
		return (ERROR);
	}
	return (SUCCESS);
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
