#include "../include/minishell.h"

/*
 * Description: 괄호의 짝이 맞는지 검사한다.
 * Param.   #1: 토큰 리스트의 첫 번째 토큰 주소
 * Param.   #2: 토큰의 값(value)을 담을 문자열 포인터
 * Return     : true : 괄호의 짝이 맞음
 *            : false: 괄호의 짝이 맞지 않음
 */
bool	is_pair_of_parenthesis(t_token *token, char **token_value)
{
	t_token	*temp;
	int		parenthesis_count;

	parenthesis_count = 0;
	temp = token;
	while (temp)
	{
		*token_value = temp->value;
		if (temp->type == PARENTHESIS_OPEN)
			parenthesis_count++;
		else if (temp->type == PARENTHESIS_CLOSE)
			parenthesis_count--;
		if (parenthesis_count < 0)
			return (false);
		temp = temp->next;
	}
	if (parenthesis_count == 0)
		return (true);
	return (false);
}

/*
 * Description: 리다이렉션 문법이 유효한지 검사한다.
 * Param.   #1: 토큰 리스트의 첫 번째 토큰 주소
 * Param.   #2: 토큰의 값(value)을 담을 문자열 포인터
 * Return     : true : 리다이렉션 문법이 유효함
 *            : false: 리다이렉션 문법이 유효하지 않음
 */
bool	is_valid_redirection(t_token *token, char **token_value)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (temp->type == REDIRECT_IN || temp->type == REDIRECT_OUT)
		{
			if (!temp->next || (temp->next->type != NORMAL
					&& temp->next->type != AMPERSAND))
			{
				*token_value = temp->value;
				return (false);
			}
		}
		else if (temp->type == DREDIRECT_IN || temp->type == DREDIRECT_OUT)
		{
			if (!temp->next || temp->next->type != NORMAL)
			{
				*token_value = temp->value;
				return (false);
			}
		}
		temp = temp->next;
	}
	return (true);
}

/*
 * Description: 괄호의 위치가 유효한지 검사한다.
 * Param.   #1: 토큰 리스트의 첫 번째 토큰 주소
 * Param.   #2: 토큰의 값(value)을 담을 문자열 포인터
 * Return     : true : 괄호가 올바른 위치에 있음
 *            : false: 괄호가 잘못된 위치에 있음
 */
bool	is_valid_parenthesis(t_token *token, char **token_value)
{
	t_token	*prev;
	t_token	*next;
	t_token	*temp;

	prev = NULL;
	temp = token;
	while (temp)
	{
		*token_value = temp->value;
		if (temp->type == PARENTHESIS_OPEN)
		{
			temp = temp->next;
			next = get_last_token_in_parenthesis(&temp);
			if (!next)
				return (false);
			next = next->next->next;
			if ((!prev || prev->type == AMPERSAND || prev->type == PIPE)
				&& (!next || next->type == AMPERSAND || next->type == PIPE))
				return (false);
		}
		prev = temp;
		temp = temp->next;
	}
	return (true);
}

/*
 * Description: 명령어의 위치가 유효한지 검사한다.
 * Param.   #1: 토큰 리스트의 첫 번째 토큰 주소
 * Param.   #2: 토큰의 값(value)을 담을 문자열 포인터
 * Return     : true : 괄호가 올바른 위치에 있음
 *            : false: 괄호가 잘못된 위치에 있음
 */
bool	is_valid_command(t_token *token, char **token_value)
{
	t_token	*temp;
	bool	is_in_normal;

	temp = token;
	is_in_normal = false;
	while (temp)
	{
		*token_value = temp->value;
		if (is_operator(temp) || temp->type == AMPERSAND)
		{
			if (!is_in_normal)
				return (false);
			is_in_normal = false;
		}
		else if (temp->type == NORMAL)
			is_in_normal = true;
		else if (temp->type == REDIRECT_IN || temp->type == REDIRECT_OUT
			|| temp->type == DREDIRECT_IN || temp->type == DREDIRECT_OUT)
			temp = temp->next;
		temp = temp->next;
	}
	return (true);
}

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
