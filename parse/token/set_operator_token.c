/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_operator_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:54:25 by yena              #+#    #+#             */
/*   Updated: 2023/05/10 20:54:26 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Description: 단일 연산자의 토큰 타입을 가져온다.
 * Param.   #1: t_token *token. 연산자 토큰.
 * Return     : 연산자의 토큰 타입
 */
enum e_token_type	get_operator_token_type(char c)
{
	if (c == '(')
		return (PARENTHESIS_OPEN);
	else if (c == ')')
		return (PARENTHESIS_CLOSE);
	else if (c == '&')
		return (AMPERSAND);
	else if (c == '<')
		return (REDIRECT_IN);
	else if (c == '>')
		return (REDIRECT_OUT);
	else if (c == '|')
		return (PIPE);
	else
		return (NORMAL);
}

/*
 * Description: 연속된 연산자의 토큰 타입을 가져온다.
 * Param.   #1: 연산자의 문자.
 * Return     : 연산자 토큰 타입
 */
enum e_token_type	get_double_operator_token_type(char c)
{
	if (c == '&')
		return (DAMPERSAND);
	else if (c == '<')
		return (DREDIRECT_IN);
	else if (c == '>')
		return (DREDIRECT_OUT);
	else if (c == '|')
		return (DPIPE);
	else
		return (NORMAL);
}

/*
 * Description: 연산자 토큰을 생성한다.
 * 				1. (, ), ;의 경우, 연산자 토큰을 생성한다.
 * 				2. &, <, >, |의 경우
 * 					2.1. 다음 문자가 연속된 연산자가 아니라면, 연산자 토큰을 생성한다.
 * 					2.2. 다음 문자가 연속된 연산자라면, 연속된 연산자 토큰을 생성한다.
 * 						예)  &&, <<, >>, ||
 * Param.   #1: 토큰 리스트의 주소를 가리키는 포인터의 주소
 * Param.   #2: 토큰화 할 문자열(= 커맨드 라인)
 * Param.   #3: 커맨드 라인에서 몇 번째 글자인지를 나타내는 인덱스 포인터
 * Return     : 없음
 */
void	set_operator_token(t_token **token, char *trimmed_line, int *i)
{
	char	*operator;

	if ((*token)->value)
		return ;
	operator = &trimmed_line[*i];
	if (ft_strchr("()", *operator))
	{
		join_token_value(token, trimmed_line, i);
		(*token)->type = get_operator_token_type(*operator);
		(*i)++;
	}
	else if (ft_strchr("<>&|", trimmed_line[*i]))
	{
		while (trimmed_line[*i] == *operator)
		{
			join_token_value(token, trimmed_line, i);
			(*i)++;
		}
		if ((&trimmed_line[*i] - operator) == 2)
			(*token)->type = get_double_operator_token_type(*operator);
		else
			(*token)->type = get_operator_token_type(*operator);
	}
}
