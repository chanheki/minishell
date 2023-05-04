#include "../../include/minishell.h"

/*
 * Description: 괄호의 짝이 맞는지 검사한다.
 * Param.   #1: 토큰 리스트의 첫 번째 토큰 주소
 * Param.   #2: 토큰의 값(value)을 담을 문자열 포인터
 * Return     : true : 괄호의 짝이 맞음
 *            : false: 괄호의 짝이 맞지 않음
 */
bool	is_pair_of_parenthesis(t_token *token)
{
	t_token	*temp;
	int		parenthesis_count;

	parenthesis_count = 0;
	temp = token;
	while (temp)
	{
		if (temp->type == PARENTHESIS_OPEN)
			parenthesis_count++;
		else if (temp->type == PARENTHESIS_CLOSE)
			parenthesis_count--;
		if (parenthesis_count < 0)
		{
			print_syntax_error(temp);
			return (false);
		}
		temp = temp->next;
	}
	if (parenthesis_count == 0)
		return (true);
	print_syntax_error(temp);
	return (false);
}

/*
 * Description: 리다이렉션 문법이 유효한지 검사한다.
 * Param.   #1: 토큰 리스트의 첫 번째 토큰 주소
 * Param.   #2: 토큰의 값(value)을 담을 문자열 포인터
 * Return     : true : 리다이렉션 문법이 유효함
 *            : false: 리다이렉션 문법이 유효하지 않음
 */
bool	is_valid_redirection(t_token *token)
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
				print_syntax_error(temp);
				return (false);
			}
		}
		else if (temp->type == DREDIRECT_IN || temp->type == DREDIRECT_OUT)
		{
			if (!temp->next || temp->next->type != NORMAL)
			{
				print_syntax_error(temp);
				return (false);
			}
		}
		temp = temp->next;
	}
	return (true);
}

/*
 * Description: 괄호 내 명령어의 문법이 올바른지 검사한다.
 * Param.   #1: 열린 괄호 토큰의 주소
 * Param.   #2: 닫힌 괄호 토큰의 주소
 * Return     : true : 괄호 내 문법이 올바름
 *            : false: 괄호 내 문법이 올바르지 않음
 */
bool	is_correct_in_parenthesis(t_token *open, t_token *close)
{
	t_token	*tokens_in_parent;

	tokens_in_parent = get_tokens_in_parenthesis(open, close);
	if (!tokens_in_parent)
		return (false);
	if (!is_valid_syntax(tokens_in_parent))
	{
		free_token_list(&tokens_in_parent);
		return (false);
	}
	free_token_list(&tokens_in_parent);
	return (true);
}

/*
 * Description: 괄호의 위치가 유효한지 검사한다.
 * 				만약 '(' 앞의 토큰이 존재할 경우, NORMAL 토큰이거나 리다이렉션이라면 false이다.
 *				만약 ')' 앞의 토큰이 노멀 토큰이 아니거나, 
 * Param.   #1: 토큰 리스트의 첫 번째 토큰 주소
 * Param.   #2: 토큰의 값(value)을 담을 문자열 포인터
 * Return     : true : 괄호가 올바른 위치에 있음
 *            : false: 괄호가 잘못된 위치에 있음
 */
bool	is_valid_parenthesis(t_token *token)
{
	t_token	*temp;
	t_token	*open;
	t_token	*close;

	temp = token;
	while (temp->next)
	{
		while (temp->next && temp->type != PARENTHESIS_OPEN)
			temp = temp->next;
		if (!temp->next)
			break ;
		open = temp;
		if (open->prev
			&& (open->prev->type == NORMAL || is_redirection(open->prev)))
		{
			print_syntax_error(temp);
			return (false);
		}
		while (temp->next && temp->type != PARENTHESIS_CLOSE)
			temp = temp->next;
		close = temp;
		if (!is_correct_in_parenthesis(open, close))
			return (false);
		temp = close;
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
bool	is_valid_command(t_token *token)
{
	t_token	*temp;
	bool	is_in_normal;

	temp = token;
	is_in_normal = false;
	while (temp)
	{
		if (is_operator(temp) || temp->type == AMPERSAND)
		{
			if (!is_in_normal)
				break ;
			is_in_normal = false;
		}
		else if (temp->type == NORMAL)
			is_in_normal = true;
		else if (temp->type == REDIRECT_IN || temp->type == REDIRECT_OUT
			|| temp->type == DREDIRECT_IN || temp->type == DREDIRECT_OUT)
			temp = temp->next;
		temp = temp->next;
	}
	if (!is_in_normal)
	{
		print_command_not_found(temp);
		return (false);
	}
	return (true);
}
