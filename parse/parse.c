void	parse_command_line(char *line)
{
	char		**trimmed_line;
	char		**token;
	t_ASTnode	**ast_nodes;
	int			i;

	trimmed_line = ft_strtrim(line, ' ');
	if (!trimmed_line)
		return ;
	preprocess_line(trimmed_line);
	i = -1;
	// TODO => create ASTnode and ASTtree
}