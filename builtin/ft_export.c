#include "../include/minishell.h"

/*
 * Description: 환경변수를 추가한다.
 * Param.   #1: 환경변수를 추가할 문자열
 * Return     : exit status를 반환한다.
 */
int	ft_export(char **argv)
{
	char	*key;
	char	*value;
	int		i;
	int		exit_status;

	i = 0;
	exit_status = 0;
	while (argv[++i])
	{
		if (check_env_argv(argv[i]))
		{
			exit_status = 1;
			continue ;
		}
		key = get_env_key(argv[i]);
		value = get_env_value(argv[i]);
		if (set_env(key, value) != SUCCESS)
			exit_status = 1;
	}
	return (exit_status);
}
