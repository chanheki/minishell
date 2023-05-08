#include "../include/minishell.h"

/*
 * Description: builtin 명령어인지 확인한다.
 * Param.   #1: cmd = path = builtin 함수 명령어
 * Return     : true = 맞음
 *            : false = 아님
 */
int	check_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

bool	is_builtin_cmd(t_ASTnode *node)
{
	const char	cmd[7][7] = {"echo", "pwd", "cd", "env", "export", \
								"unset", "exit"};
	int			i;

	if (!node || !node->token)
	{
		ft_putendl_fd("is_builtin_cmd : node error", STDERR_FILENO);
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
		return (ft_unset(argv));
	printf("exec_builtin : invalid %s \n", path);
	ft_putendl_fd("exec_builtin : invalid path", STDERR_FILENO);
	return (EXIT_BUILT_IN_FAIL);
}
