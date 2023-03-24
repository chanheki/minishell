#include "../../include/parse.h"

/*
 * Description: 이전 foreground에서 실행된 명령어의 exit status를 토큰의 value에 저장한다.
 * Param.   #1: 토큰의 주소
 * Param.   #2: 해석할 환경변수가 포함된 커맨드 라인
 * Param.   #3: 커맨드 라인 내 환경변수의 시작 인덱스. '?'의 위치를 가리키고 있음
 * Return     : 없음
 */
void	interpret_exit_status(t_token **token, int *i)
{
	char	*exit_status;
	char	*temp;

	exit_status = ft_itoa(0);
	if (!(*token)->value)
		(*token)->value = exit_status;
	else
	{
		temp = (*token)->value;
		(*token)->value = ft_strjoin((*token)->value, exit_status);
		free(temp);
		free(exit_status);
	}
	*i += 2;
}

/*
 * Description: 환경변수 키를 찾아서 그 값을 반환한다.
 * Param.   #1: 환경변수 키를 찾을 문자열
 * Param.   #2: 환경변수 키가 시작되는 인덱스
 * Param.   #3: 환경변수 키의 길이
 * Return     : 환경변수 키에 해당하는 값
 */
char	*get_env_value(char *trimmed_line, int start, int length)
{
	char	*env_name;
	char	*interpreted;

	env_name = ft_substr(trimmed_line, start, length);
	interpreted = getenv(env_name);
	free(env_name);
	return (interpreted);
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
	char	*interpreted;
	char	*new_token_value;
	int		length;

	(*i)++;
	length = 0;
	while (trimmed_line[*i + length] && trimmed_line[*i + length] != BLANK
		&& !ft_strchr("<>()|;&\'\"", trimmed_line[*i + length]))
		length++;
	interpreted = get_env_value(trimmed_line, *i, length);
	*i += length;
	if (!interpreted)
		return ;
	if ((*token)->value)
	{
		new_token_value = ft_strjoin((*token)->value, interpreted);
		free((*token)->value);
		(*token)->value = new_token_value;
	}
	else
		(*token)->value = ft_strdup(interpreted);
}

/*
 * Description: 환경변수를 해석한다.
 *              1. *i번째 다음 글자가 없거나 큰 따옴표로 감싸진다면, $만 토큰의 값에 이어붙인다.
 *              2. $ 다음 글자가 ?이면, exit status를 토큰의 값에 이어붙인다.
 *              3. $ 다음에 환경변수 키가 온다면, 그에 해당하는 값을 토큰의 값에 이어붙인다.
 * Param.   #1: 토큰의 주소
 * Param.   #2: 해석할 환경변수가 포함된 커맨드 라인
 * Param.   #3: 커맨드 라인 내 환경변수의 시작 인덱스
 * Return     : 없음
 */
void	interpret_expansion(t_token **token, char *trimmed_line, int *i)
{
	if (trimmed_line[*i + 1] == '?')
		interpret_exit_status(token, i);
	else if (trimmed_line[*i + 1] == '\0'
		|| ((*token)->is_in_dquote && trimmed_line[*i + 1] == DQUOTE)
		|| ((*token)->prev && (*token)->prev->type == DREDIRECT_IN))
	{
		join_token_value(token, trimmed_line, i);
		(*i)++;
		return ;
	}
	else
		interpret_env(token, trimmed_line, i);
}
