#include "../include/minishell.h"

/*
 * Description: builtin 명령어인지 확인한다.
 *            : node가 정상 노드인지 확인하고, 
 *            : node->token->value == builtin
 * Param.   #1: node
 * Return     : true = 맞음
 *            : false = 아님
 */
bool	is_builtin_command(t_ASTnode *node)
{
	int			i;
	const char	cmd[8][8] = {"cd", \
							"echo", \
							"env", \
							"exit", \
							"export", \
							"pwd", \
							"unset"};

	if (!(node->token->value))
		return (true);
	if (!node || !node->token)
	{
		ft_putendl_fd("is_builtin_command : node error", STDERR_FILENO);
		return (false);
	}
	if (node->token->type != NORMAL)
		return (false);
	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(node->token->value, (char *)(cmd[i])))
			return (true);
		i++;
	}
	return (false);
}

/*
 * Description: excute builtin 명령어를 실행한다.
 *            : builtin 함수를 실행한다.
 * Param.   #1: path = builtin 함수 명령어
 *          #2: argv = 해당 명령어의 option 값들
 * Return     : SUCCESS : 성공
 *            : EXIT_BUILT_IN_FAIL = 2 실패
 */
int	execute_builtin(char *path, char **argv, t_process_type type)
{
	if (!path)
	{
		// ft_putendl_fd("execute_builtin : command not found", STDERR_FILENO);
		return (0);
	}
	if (!ft_strcmp(path, "cd"))
		return (ft_cd(argv + 1));
	else if (!ft_strcmp(path, "echo"))
		return (ft_echo(argv));
	else if (!ft_strcmp(path, "env"))
		return (ft_env());
	else if (!ft_strcmp(path, "exit"))
		return (ft_exit(argv, type));
	else if (!ft_strcmp(path, "export"))
		return (ft_export(argv));
	else if (!ft_strcmp(path, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(path, "unset"))
		return (ft_unset(argv));
	ft_putendl_fd("execute_builtin : invalid path", STDERR_FILENO);
	return (EXIT_BUILT_IN_FAIL);
}
