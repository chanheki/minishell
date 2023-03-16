#include "../../include/parse.h"

/*
 * Description: 토큰 리스트의 메모리를 해제한다.
 * Param      : 해제할 토큰 리스트
 * Return     : void
 */
void	free_token_list(t_token **token)
{
	t_token	*temp;

	if (!token)
		return ;
	while (*token)
	{
		temp = (*token)->next;
		if ((*token)->value)
		{
			free((*token)->value);
			(*token)->value = NULL;
		}
		free(*token);
		*token = temp;
	}
	*token = NULL;
}
