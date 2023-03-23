#include "../../include/parse.h"

/*
 * Description: 토큰의 값에서 바깥 따옴표의 위치에는 delete_flag에 't'를, 그 외에는 'f'를 넣는다.
 *              추후 delete_flag의 't'인 위치의 따옴표를 삭제한다.
 *              만약 따옴표가 짝이 맞지 않는다면, 마지막으로 닫히지 않은 따옴표는 삭제하지 않는다.
 *              예를 들어, "echo의 경우, "는 삭제하지 않는다.
 * Param.   #1: 토큰의 값
 * Param.   #2: 삭제할 따옴표 위치를 표시할 문자열
 * Return     : 없음
 */
void	check_delete_quote(char *value, char *delete_flag)
{
	int		i;
	char	quote_type;

	i = -1;
	quote_type = 0;
	while (value[++i])
	{
		if (!quote_type && is_quote(value[i]))
		{
			quote_type = value[i];
			delete_flag[i] = 't';
		}
		else if (quote_type && value[i] == quote_type)
		{
			quote_type = 0;
			delete_flag[i] = 't';
		}
		else
			delete_flag[i] = 'f';
	}
	while (quote_type && --i >= 0)
	{
		if (value[i] == quote_type)
			delete_flag[i] = 'f';
	}
}

/*
 * Description: 토큰의 값에서 delete_flag의 't'인 위치의 따옴표를 삭제한다.
 *              그리고 따옴표가 삭제된 문자열을 생성하여 새로운 토큰의 값으로 할당한다.
 * Param.   #1: 토큰의 주소
 * Param.   #2: 삭제할 따옴표 위치를 표시한 문자열
 * Return     : 없음
 */
void	rebuild_quote_string(t_token **temp_token, char *delete_flag)
{
	int		i;
	int		length;
	char	*new_value;

	i = -1;
	length = 0;
	while (delete_flag[++i])
	{
		if (delete_flag[i] == 'f')
			length++;
	}
	new_value = (char *)ft_calloc(length + 1, sizeof(char));
	i = -1;
	length = 0;
	while (delete_flag[++i])
	{
		if (delete_flag[i] == 'f')
			new_value[length++] = (*temp_token)->value[i];
	}
	free((*temp_token)->value);
	(*temp_token)->value = new_value;
}

/*
 * Description: NORMAL 토큰에 한하여 맨 앞/맨 뒤 따옴표를 제거한다.
 * Param.   #1: 토큰 리스트
 * Return     : 없음
 */
void	delete_outer_quotes(t_token **token)
{
	t_token	*temp_token;
	char	*delete_flag;

	if (!token)
		return ;
	temp_token = *token;
	while (temp_token)
	{
		if (temp_token->type == NORMAL && temp_token->value)
		{
			delete_flag = (char *)ft_calloc(ft_strlen(temp_token->value) + 1,
					sizeof(char));
			check_delete_quote(temp_token->value, delete_flag);
			rebuild_quote_string(&temp_token, delete_flag);
			free(delete_flag);
		}
		temp_token = temp_token->next;
	}
}
