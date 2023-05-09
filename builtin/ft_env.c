#include "../include/minishell.h"

/*
 * Description: 환경변수를 출력한다.
 * Param.     : 없음
 * Return     : 없음
 */
int	ft_env(void)
{
	int	i;

	i = -1;
	while (g_var.envp[++i])
	{
		ft_putstr_fd(g_var.envp[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (0);
}
