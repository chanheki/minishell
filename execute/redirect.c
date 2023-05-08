#include "../include/minishell.h"
#include <fcntl.h>

static t_error	set_infile(char *path, bool heredoc)
{
	int	in_fd;

	in_fd = open(path, O_RDONLY, 0644);
	if (in_fd == -1)
	{
		ft_putstr_fd("JIP-Shell: ", 2);
		perror(path);
		return (ERROR);
	}
	if (heredoc)
		unlink(path);
	return (ft_dup2(in_fd, STDIN_FILENO));
}

static t_error	set_outfile(char *path, bool type)
{
	int			out_fd;
	const bool	trunc = false;
	const bool	append = true;

	out_fd = -1;
	if (type == trunc)
		out_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == append)
		out_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out_fd == -1)
		return (ERROR);
	return (ft_dup2(out_fd, STDOUT_FILENO));
}

t_error	redirection(t_ASTnode *node)
{
	t_token	*token;
	char	*file;

	file = node->left->token->value;
	token = node->token;
	if (check_token_type(token, REDIRECT_IN))
		return (set_infile(file, false));
	else if (check_token_type(token, DREDIRECT_IN))
		return (set_infile(file, true));
	else if (check_token_type(token, REDIRECT_OUT))
		return (set_outfile(file, false));
	else if (check_token_type(token, DREDIRECT_OUT))
		return (set_outfile(file, true));
	return (ERROR);
}

t_error	redirect(t_ASTnode *node)
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
