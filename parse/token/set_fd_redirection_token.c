#include "../../include/parse.h"

/*
 * Description: 파일 디스크립터가 주어진 리다이렉션 토큰을 생성한다.
 * 				1. *i번째 문자가 파일 디스크립터(숫자만)일 경우, 그대로 토큰의 값에 이어 붙인다.
 * 				2. *i번째 문자가 <, > 등의 리다이렉션을 나타낸다면, 연산자 토큰을 생성하는 함수를 호출한다.
 * 				3. *i번째 문자가 (, ), ;, &, |라면, 함수를 종료한다.
 * 				4. *i번째 문자가 숫자가 아닌, 다른 글자라면, 일반 토큰을 생성하는 함수를 호출한다.
 * Param.   #1: 토큰 리스트의 주소를 가리키는 포인터의 주소
 * Param.   #2: 토큰화 할 문자열(= 커맨드 라인)
 * Param.   #3: 커맨드 라인에서 몇 번째 글자인지를 나타내는 인덱스 포인터
 * Return     : 없음
 */
void	set_fd_redirection_token(t_token **token, char *trimmed_line, int *i)
{
	while (trimmed_line[*i] && ft_isdigit(trimmed_line[*i]))
	{
		join_token_value(token, trimmed_line, i);
		(*i)++;
	}
	if (trimmed_line[*i] && trimmed_line[*i] != BLANK)
	{
		if (ft_strchr("<>", trimmed_line[*i]))
			set_operator_token(token, trimmed_line, i);
		else if (ft_strchr("();&|", trimmed_line[*i]))
			return ;
		else
			set_normal_token(token, trimmed_line, i);
	}
}
