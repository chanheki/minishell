#include "../include/minishell.h"

void	print_ast_tree(t_ASTnode *ast_tree)
{
	t_ASTnode	*leftmost;
	t_ASTnode	*rightmost;

	if (!ast_tree)
		return ;
	leftmost = ast_tree;
	while (leftmost->left)
		leftmost = leftmost->left;
	ft_putstr_fd("leftmost : ", STDOUT_FILENO);
	if (leftmost == ast_tree)
		ft_putstr_fd("(null)", STDOUT_FILENO);
	else
		ft_putstr_fd(leftmost->token->value, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	ft_putstr_fd("root     : ", STDOUT_FILENO);
	ft_putstr_fd(ast_tree->token->value, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	rightmost = ast_tree;
	while (rightmost->right)
		rightmost = rightmost->right;
	ft_putstr_fd("rightmost: ", STDOUT_FILENO);
	if (rightmost == ast_tree)
		ft_putstr_fd("(null)", STDOUT_FILENO);
	else
		ft_putstr_fd(rightmost->token->value, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

int	main(void)
{
	char		*input;
	char		*trimmed;
	int 		read_bytes;
	t_token		*token;
	t_ASTnode 	*ast_tree;

	input = (char *)malloc(sizeof(char) * (BUFSIZ + 1));
	while (1)
	{
		ft_putstr_fd("type command line => ", STDOUT_FILENO);
		read_bytes = read(STDIN_FILENO, input, BUFSIZ);
		if (read_bytes < 1)
			break ;
		input[read_bytes] = '\0';
		trimmed = ft_strtrim(input, " \n");
		token = tokenize_line(trimmed);
		free(trimmed);
		if (is_valid_syntax(token))
		{
			delete_outer_quotes(&token);
			ast_tree = make_ast_tree(&token);
			handle_wildcard(ast_tree);
			print_ast_tree(ast_tree);
			ft_putstr_fd("SUCCESS\n", STDOUT_FILENO);
		}
		free_token_list(&token);
		ft_memset(input, 0, read_bytes);
	}
	free(input);
	return (0);
}
