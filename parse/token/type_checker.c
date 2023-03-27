#include "../../include/minishell.h"

/*
 * Description: 현재 토큰이 연산자인지 확인한다.
 * Param.   #1: 확인할 토큰
 * Return     : true : 연산자가 맞음
 *              false: 연산자가 아님
 */
bool	is_operator(t_token *token)
{
	if (token->type == PIPE
		|| token->type == DAMPERSAND || token->type == DPIPE)
		return (true);
	return (false);
}

/*
 * Description: 현재 문자가 따옴표인지 확인한다.
 * Param.   #1: 확인할 문자
 * Return     : true : 따옴표가 맞음
 *              false: 따옴표가 아님
 */
bool	is_quote(char c)
{
	if (c == QUOTE || c == DQUOTE)
		return (true);
	return (false);
}
