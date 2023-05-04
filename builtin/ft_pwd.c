
// pwd with no options

// 　옵션이 없는 pwd

#include "../include/minishell.h"

int	ft_pwd(char **argv)
{
	char	*path;

	argv = (char **)argv;
	path = getcwd(NULL, 0);
	if (!path)
		return (1);
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	path = NULL;
	return (0);
}
