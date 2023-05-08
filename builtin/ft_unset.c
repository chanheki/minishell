#include "../include/minishell.h"

/*
 * Description: 유효한 env 키 형식인지 확인한다.
 *              유효한 env 키 형식은 첫 글자가 알파벳인 경우에 해당한다.
 * Param.   #1: env 키를 담고 있는 문자열
 * Return     : 없음
 */
void	check_unset_argv(char *argv)
{
	if (!((*argv >= 'A' && *argv <= 'Z')
			|| (*argv >= 'a' && *argv <= 'z')))
	{
		ft_putstr_fd("minishell: unset: ", STDERR_FILENO);
		ft_putstr_fd(argv, STDERR_FILENO);
		ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
		g_var.exit_status = 1;
	}
}

/*
 * Description: 주어진 문자열들을 키로 하는 env 값을 지운다.
 * Param.   #1: 'unset'을 포함하여 env 키들을 담고 있는 문자열 포인터
 * Return     : 0
 */
int	ft_unset(char **argv)
{
	char	*env;
	int		i;

	i = 0;
	while (argv[++i])
	{
		check_unset_argv(argv[i]);
		env = getenv(argv[i]);
		if (env)
			*env = '\0';
	}
	return (0);
}
