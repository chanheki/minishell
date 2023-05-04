#include "../../include/minishell.h"

/*
 * Description: 토큰의 문법 유효성을 검사한다.
 *              1. 괄호의 짝이 맞는지 검사한다.
 *              2. 괄호의 위치가 올바른지 검사한다.
 *              3. 리다이렉션의 위치가 올바른지 검사한다.
 *              4. 명령어의 위치가 올바른지 검사한다.
 * Param.   #1: 토큰 리스트의 첫 번째 토큰 주소
 * Return     : true : 유효한 문법
 *              false: 유효하지 않은 문법
 */
bool	is_valid_syntax(t_token *token)
{
	char	*token_value;

	if (!is_pair_of_parenthesis(token, &token_value)
		|| !is_valid_parenthesis(token, &token_value)
		|| !is_valid_redirection(token, &token_value))
	{
		ft_putstr_fd("JIP-shell: syntax error near unexpected token `", 2);
		ft_putstr_fd(token_value, 2);
		ft_putendl_fd("'", 2);
		return (false);
	}
	else if (!is_valid_command(token, &token_value))
	{
		ft_putstr_fd("JIP-shell: command not found: ", 2);
		ft_putendl_fd(token_value, 2);
		return (false);
	}
	return (true);
}
