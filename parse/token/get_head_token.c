#include "../../include/parse.h"

/*
 * Description: 토큰 리스트의 맨 앞 토큰을 반환한다.
 * Param.  #1 : 토큰 리스트
 * Return     : 토큰 리스트의 맨 앞 토큰
 */
t_token	*get_head_token(t_token **token)
{
	if (!token || !*token)
		return (NULL);
	while ((*token)->prev)
		*token = (*token)->prev;
	return (*token);
}
