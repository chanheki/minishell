#include "../include/minishell.h"

int	check_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") 
	|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "env") 
	|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "export") 
	|| !ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

int	exec_builtin(char *path, char **argv)
{
	if (!ft_strcmp(path, "cd"))
		return (ft_cd(argv));
	else if (!ft_strcmp(path, "echo"))
		return (ft_echo(argv));
	else if (!ft_strcmp(path, "env"))
		return (ft_env());
	else if (!ft_strcmp(path, "exit"))
		return (ft_exit());
	else if (!ft_strcmp(path, "export"))
		return (ft_export());
	else if (!ft_strcmp(path, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(path, "unset"))
		return(ft_unset(argv));
	ft_putendl_fd("exec_builtin : invalid path", STDERR_FILENO);
	return (-1);
}
