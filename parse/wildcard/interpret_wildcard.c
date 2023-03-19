#include "../../include/parse.h"

bool	is_valid_wildcard(t_token *token, char *token_value, char *dir_name)
{
	size_t	value_length;
	size_t	dir_length;
	size_t	i;
	size_t	dir_idx;

	value_length = ft_strlen(token_value);
	dir_length = ft_strlen(dir_name);
	i = 0;
	while (i < value_length && i < dir_length && (token_value[i] == dir_name[i]))
		i++;
	if (i == value_length)
		return (i == dir_length);
	if (token->type == WILDCARD)
	{
		dir_idx = 0;
		while (i + dir_idx <= dir_length)
		{
			if (is_valid_wildcard(token, token_value + i + 1, dir_name + i + dir_idx))
				return (true);
			dir_idx++;
		}
	}
	return (false);
}

int	rebuild_wildcard(t_ASTnode **node, int *dir_count, char *dir_name)
{
	t_token		*token;
	t_token		*new_token;
	t_ASTnode	*new_node;

	token = (*node)->token;
	if (*dir_count == 0)
	{
		free(token->value);
		token->value = ft_strdup(dir_name);
	}
	else
	{
		new_token = create_new_token(dir_name, WILDCARD);
		new_node = create_new_node(new_token, WILDCARD);
		if (!new_node || !new_token)
			return (ERROR);
		add_node_to_direction(node, new_node, LEFT);
		*node = new_node;
	}
	(*dir_count)++;
	return (SUCCESS);
}



int	interpret_wildcard(t_ASTnode **node)
{
	DIR						*dir;
	static struct dirent	*dirent;
	int						dir_count;

	dir = opendir(".");
	dir_count = 0;
	if (!dir)
		return (ERROR);
	while (1)
	{
		dirent = readdir(dir);
		if (!dirent)
			break ;
		if (is_valid_wildcard((*node)->token, (*node)->token->value, dirent->d_name)
			&& rebuild_wildcard(node, &dir_count, dirent->d_name) == ERROR)
		{
			closedir(dir);
			return (ERROR);
		}
	}
	if (closedir(dir) == -1 || errno)
		return (ERROR);
	return (SUCCESS);
}

int	handle_wildcard(t_ASTnode *ast_tree)
{
	if (!ast_tree)
		return (SUCCESS);
	if (ast_tree->token->type == NORMAL)
	{
		if (handle_wildcard(ast_tree->left) == ERROR
			|| handle_wildcard(ast_tree->right) == ERROR)
			return (ERROR);
		if (!ft_strchr(ast_tree->token->value, WILDCARD))
			return (SUCCESS);
		ast_tree->token->type = WILDCARD;
		if (interpret_wildcard(&ast_tree) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
