#include "../../include/minishell.h"

/*
 * Description: 작은 따옴표 토큰을 생성한다.
 *              다음 작은 따옴표를 만날 때까지 토큰의 값을 이어 붙임으로써 토큰을 생성한다.
 * Param.   #1: 토큰 리스트의 주소를 가리키는 포인터의 주소
 * Param.   #2: 토큰화 할 문자열(= 커맨드 라인)
 * Param.   #3: 커맨드 라인에서 몇 번째 글자인지를 나타내는 인덱스 포인터
 * Return     : 없음
 */
void	set_single_quote_token(t_token **token, char *trimmed_line, int *i)
{
	while (trimmed_line[*i] && trimmed_line[*i] != QUOTE)
	{
		join_token_value(token, trimmed_line, i);
		(*i)++;
	}
	join_token_value(token, trimmed_line, i);
	if ((*token)->is_in_quote && trimmed_line[*i] == QUOTE)
	{
		(*token)->is_in_quote = false;
		(*i)++;
	}
	set_token(token, trimmed_line, i);
}

/*
 * Description: 큰 따옴표 토큰을 생성한다. 내부에 환경변수가 있다면, 해석한다.
 *              다음 큰 따옴표를 만날 때까지 토큰의 값을 이어 붙임으로써 토큰을 생성한다.
 *              환경변수가 있다면, 해석한다.
 * Param.   #1: 토큰 리스트의 주소를 가리키는 포인터의 주소
 * Param.   #2: 토큰화 할 문자열(= 커맨드 라인)
 * Param.   #3: 커맨드 라인에서 몇 번째 글자인지를 나타내는 인덱스 포인터
 * Return     : 없음
 */
void	set_double_quote_token(t_token **token, char *trimmed_line, int *i)
{
	while (trimmed_line[*i] && trimmed_line[*i] != DQUOTE)
	{
		if (trimmed_line[*i] != EXPANSION)
			join_token_value(token, trimmed_line, i);
		if (!((*token)->is_in_escape) && trimmed_line[*i] == ESCAPE)
			(*token)->is_in_escape = true;
		else if (!(*token)->is_in_escape && trimmed_line[*i] == EXPANSION)
		{
			interpret_expansion(token, trimmed_line, i);
			continue ;
		}
		(*i)++;
	}
	join_token_value(token, trimmed_line, i);
	if ((*token)->is_in_dquote && trimmed_line[*i] == DQUOTE)
	{
		(*token)->is_in_dquote = false;
		(*i)++;
	}
	set_token(token, trimmed_line, i);
	return ;
}

/*
 * Description: 작은 따옴표 및 큰 따옴표가 나오면 각각에 해당하는 토큰을 생성한다.
 * Param.   #1: 토큰 리스트의 주소를 가리키는 포인터의 주소
 * Param.   #2: 토큰화 할 문자열(= 커맨드 라인)
 * Param.   #3: 커맨드 라인에서 몇 번째 글자인지를 나타내는 인덱스 포인터
 * Return     : 없음
 */
void	set_quote_token(t_token **token, char *trimmed_line, int *i)
{
	join_token_value(token, trimmed_line, i);
	if (trimmed_line[*i] == QUOTE)
	{
		(*i)++;
		(*token)->is_in_quote = true;
		set_single_quote_token(token, trimmed_line, i);
	}
	else if (trimmed_line[*i] == DQUOTE)
	{
		(*i)++;
		(*token)->is_in_dquote = true;
		set_double_quote_token(token, trimmed_line, i);
	}
}
