#include "../../include/parse.h"

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
