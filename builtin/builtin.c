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

int	exec_builtin(t_cmd_list cmd_list)
{
	if (cmd_list.cmd == "cd")
		ft_cd(cmd_list.option);
	else if (cmd_list.cmd == "echo")
		ft_echo(cmd_list.option);
	else if (cmd_list.cmd == "env")
		ft_env();
	else if (cmd_list.cmd == "exit")
		ft_exit();
	else if (cmd_list.cmd == "export")
		ft_export();
	else if (cmd_list.cmd == "pwd")
		ft_pwd();
	else if (cmd_list.cmd == "unset")
		ft_unset();
	else
		return(0);
	return (1);
}