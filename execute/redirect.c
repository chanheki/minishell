#include "../include/minishell.h"
#include <fcntl.h>

static t_error	set_infile(char *path, bool heredoc)
{
	int	in_fd;

	in_fd = open(path, O_RDONLY, 0644);
	if (in_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(path);
		return (ERROR);
	}
	if (heredoc)
		unlink(path);
	return (ft_dup2(in_fd, STDIN_FILENO));
}

static t_error	set_outfile_trunc(char *path)
{
	int	out_fd;

	out_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd == -1)
		return (ERROR);
	return (ft_dup2(out_fd, STDOUT_FILENO));
}

static t_error	set_outfile_append(char *path)
{
	int	out_fd;

	out_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out_fd == -1)
		return (ERROR);
	return (ft_dup2(out_fd, STDOUT_FILENO));
}

t_error	redirection(t_ASTnode *node)
{
	t_token	*token;
	char	*path;

	path = node->left->token->value;
	token = node->token;
	if (check_token_type(token, REDIRECT_IN) == 0)
		return (set_infile(path, false));
	else if (check_token_type(token, DREDIRECT_IN) == 0)
		return (set_infile(path, true));
	else if (check_token_type(token, REDIRECT_OUT) == 0)
		return (set_outfile_trunc(path));
	else if (check_token_type(token, DREDIRECT_OUT) == 0)
		return (set_outfile_append(path));
	return (ERROR);
}

t_error	apply_redirections(t_ASTnode *node)
{
	if (!node)
		return (ERROR);
	node = node->right;
	while (node)
	{
		if (redirection(node) == ERROR)
			return (ERROR);
		node = node->right;
	}
	return (SUCCESS);
}
