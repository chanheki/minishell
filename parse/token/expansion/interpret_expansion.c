#include "../../../include/minishell.h"

/*
 * Description: 환경변수 키를 찾아서 그 값을 반환한다.
 * Param.   #1: 환경변수 키를 찾을 문자열
 * Param.   #2: 환경변수 키가 시작되는 인덱스
 * Param.   #3: 환경변수 키의 길이
 * Return     : 환경변수 키에 해당하는 값
 */
char	*get_interpreted_env(char *trimmed_line, int start, int length)
{
	char	*key;
	char	*interpreted;

	key = ft_substr(trimmed_line, start, length);
	interpreted = find_value(key);
	free(key);
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
	interpreted = get_interpreted_env(trimmed_line, *i, length);
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
 * Description: 토큰의 문자열을 토큰화 한다.
 * Param.   #1: 토큰화 할 문자열이 포함된 토큰
 * Return     : 없음
 */
void	sub_tokenize(t_token **token)
{
	t_token	*sub_token;
	t_token	*sub_token_tail;

	sub_token = tokenize_line((*token)->value);
	if (sub_token)
	{
		sub_token->prev = (*token)->prev;
		if ((*token)->prev)
			(*token)->prev->next = sub_token;
		sub_token_tail = get_tail_token(&sub_token);
		sub_token_tail->next = (*token)->next;
		if ((*token)->next)
			(*token)->next->prev = sub_token_tail;
		free((*token)->value);
		free(*token);
		*token = sub_token;
	}
}

/*
 * Description: expansion 해석 후, 다음의 동작을 수행 하여 토큰의 값을 수정 한다.
 *              1. 토큰의 값의 앞 뒤 공백을 제거 한다.
 *              2. 토큰의 값이 공백으로 나누어진 문자열 이라면, 토큰화 한다.
 * Param.   #1: 토큰의 주소
 * Return     : 없음
 */
void	postprocess_expansion(t_token **token)
{
	char	*trimmed_value;

	if (!(*token)->value)
		return ;
	trimmed_value = ft_strtrim((*token)->value, " ");
	free((*token)->value);
	(*token)->value = trimmed_value;
	delete_outer_quotes(token);
	if (ft_strchr((*token)->value, BLANK))
		sub_tokenize(token);
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
	{
		interpret_env(token, trimmed_line, i);
		postprocess_expansion(token);
	}
}
