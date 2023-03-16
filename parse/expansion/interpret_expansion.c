#include "../../include/parse.h"

void	interpret_exit_status(t_token **token, char *trimmed_line, int *i)
{

}

/*
 * Description: 환경변수를 해석하여 토큰의 값에 이어붙인다.
 *              1. *i를 1 증가시켜 $의 다음 인덱스로 만든다.
 *              2. 커맨드 라인의 *i번째 글자가 공백/끝이 아니고, 리다이렉션/연산자/괄호가 아닐 때까지의 길이를 구한다.
 *              3. 환경변수의 이름만 추출한다.
 *              4. 환경변수의 이름으로 값을 가져온다.
 *              5. 환경변수의 값을 토큰의 값(value)에 이어붙인다.
 * Param.   #1: 토큰의 주소
 * Param.   #2: 해석할 환경변수가 포함된 커맨드 라인
 * Param.   #3: 커맨드 라인 내 환경변수의 시작 인덱스
 * Return     : 없음
 */
void	interpret_env(t_token **token, char *trimmed_line, int *i)
{
	char	*env_name;
	char	*interpreted;
	char	*new_token_value;
	int 	length;

	length = 0;
	while (trimmed_line[*i + length] && trimmed_line[*i + length] != SPACE
		   && !ft_strchr("<>()|;&\'\"", trimmed_line[*i + length]))
		length++;
	env_name = ft_substr(trimmed_line, *i, length);
	interpreted = getenv(env_name);
	free(env_name);
	*i += length;
	if (interpreted)
	{
		if ((*token)->value)
		{
			new_token_value = ft_strjoin((*token)->value, interpreted);
			free((*token)->value);
			(*token)->value = new_token_value;
		}
		else
			(*token)->value = ft_strdup(interpreted);
	}
}

void	interpret_expansion(t_token **token, char *trimmed_line, int *i)
{
	if (trimmed_line[*i] == '?')
		interpret_exit_status(token, trimmed_line, i);
	else
		interpret_env(token, trimmed_line, i);
}