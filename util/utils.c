
#include "../include/minishell.h"
#include <sys/stat.h>

t_error	ft_dup2(int fd1, int fd2)
{
	if (close(fd2) == -1)
		return (ERROR);
	if (dup2(fd1, fd2) == -1)
		return (ERROR);
	if (close(fd1) == -1)
		return (ERROR);
	return (SUCCESS);
}

bool	is_directory(char *path)
{
	struct stat	file_info;

	if (lstat(path, &file_info) < 0)
		return (false);
	if ((S_IFMT & file_info.st_mode) == S_IFDIR)
		return (true);
	return (false);
}

int	check_token_type_operator(t_token *token)
{
	if (token == NULL || token->value == NULL)
		return (false);
	if (token->type == DAMPERSAND || token->type == DPIPE)
		return (true);
	return (false);
}

int	check_token_type(t_token *token, t_token_type type)
{
	if (token == NULL || token->value == NULL)
		return (false);
	if (token->type == (t_token_type)(type))
		return (true);
	return (false);
}