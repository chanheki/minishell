#include "../include/parse.h"

/*
 * Description: 커맨드 라인을 파싱하여 토큰으로 분리 후, AST Tree를 생성한다.
 * Param.   #1: 커맨드 라인
 * Return     : AST Tree의 루트 노드
 */
t_ASTnode	*parse_command_line(char *line)
{
	char		*trimmed_line;
	t_token		*token;
	t_ASTnode	*ast_tree;

	trimmed_line = ft_strtrim(line, " ");
	if (!trimmed_line)
		return (NULL);
	token = tokenize_line(trimmed_line);
	free(trimmed_line);
	if (!token)
		return (NULL);
	if (!is_valid_syntax(token))
	{
		free_token_list(&token);
		return (NULL);
	}
	ast_tree = make_ast_tree(&token);
	if (!ast_tree)
		return (NULL);
	return (ast_tree);
}
