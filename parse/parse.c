/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:54:55 by yena              #+#    #+#             */
/*   Updated: 2023/05/11 11:46:35 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		return (free(line), NULL);
	if (!is_valid_syntax(token))
	{
		free_token_list(&token);
		return (free(line), NULL);
	}
	delete_outer_quotes(&token);
	ast_tree = make_ast_tree(&token);
	handle_wildcard(ast_tree);
	if (!ast_tree)
		return (free(line), free_token_list(&token), NULL);
	return (ast_tree);
}
