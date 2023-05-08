#include "../../include/minishell.h"

/*
 * Description: 일반 토큰을 생성한다. 여기서 일반 토큰이란, 이스케이프 문자를 포함하고 기타 연산자들을 제외한 토큰을 의미한다.
 *              토큰화 할 문자열이 더 이상 없거나, 토큰화 대상 문자가 공백 또는 연산자(<>()|;&)일 경우, 동작을 종료한다.
 *              1. 현재 문자가 따옴표라면, 따옴표를 포함한 토큰을 생성한다.
 *              2. 현재 문자가 연산자라면, 함수를 종료한다.
 *              3. 현재 문자가 이스케이프 일 때, 그 다음에도 이스케이프 문자가 나온다면,
 *                 이스케이프 문자 하나로만 토큰화 한다.
 *              4. 일반적인 문자의 경우, 그대로 토큰화 한다.
 * Param.   #1: 토큰 리스트의 주소
 * Param.   #2: 토큰화 할 문자열(= 커맨드 라인)
 * Param.   #3: 커맨드 라인에서 몇 번째 글자인지를 나타내는 인덱스 포인터
 * Return     : 없음
 */
void	set_normal_token(t_token **token, char *trimmed_line, int *i)
{
	while (trimmed_line[*i] && trimmed_line[*i] != BLANK)
	{
		if (is_quote(trimmed_line[*i]))
		{
			set_quote_token(token, trimmed_line, i);
			continue ;
		}
		else if (ft_strchr("<>()|&", trimmed_line[*i]))
			return ;
		else if (!((*token)->is_in_escape) && trimmed_line[*i] == ESCAPE)
		{
			(*token)->is_in_escape = true;
			join_token_value(token, trimmed_line, i);
			(*i)++;
			continue ;
		}
		else if (!(*token)->is_in_escape && trimmed_line[*i] == EXPANSION)
		{
			interpret_expansion(token, trimmed_line, i);
			continue ;
		}
		(*token)->is_in_escape = false;
		join_token_value(token, trimmed_line, i);
		(*i)++;
	}
}
