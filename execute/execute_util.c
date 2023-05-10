#include "../include/minishell.h"

pid_t	*make_empty_pid_list(t_ASTnode **cmd_list)
{
	pid_t	*pid_list;
	int		i;

	i = 0;
	while (cmd_list[i])
		i++;
	pid_list = (pid_t *)ft_calloc(i + 1, sizeof(pid_t));
	return (pid_list);
}

int	wait_process(pid_t *pid_list)
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
