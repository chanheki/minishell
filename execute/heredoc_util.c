#include "../include/minishell.h"

static char	*generate_random_heredoc_filename(void)
{
	char	*res;
	char	*path;
	int		fd;
	int		i;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (NULL);
	res = (char *)ft_calloc(sizeof(char), 31);
	read(fd, res, 30);
	if (!res || close(fd) < 0)
	{
		free(res);
		return (NULL);
	}
	i = 31;
	while (--i)
		res[i] = ft_abs(res[i]) % 26 + 'A';
	res[0] = '/';
	path = ft_strjoin(g_var.tmp_path, res);
	free(res);
	return (path);
}

static void	heredoc_readline(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter) || g_var.is_signal)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

static void	replace_node_value(t_ASTnode *node, char *random_file_name)
{
	t_token	*path;

	path = node->left->token;
	path->value = NULL;
	free(path->value);
	path->value = random_file_name;
}

t_error	execute_heredoc(t_ASTnode *node)
{
	char	*delimiter;
	char	*random_file_name;
	int		fd;

	delimiter = node->left->token->value;
	random_file_name = generate_random_heredoc_filename();
	if (!random_file_name)
		return (ERROR);
	fd = open(random_file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return (ERROR);
	heredoc_readline(fd, delimiter);
	replace_node_value(node, random_file_name);
	if (g_var.is_signal)
		unlink(random_file_name);
	if (close(fd) == -1)
		return (ERROR);
	return (SUCCESS);
}
