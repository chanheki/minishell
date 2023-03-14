#include "../../include/parse.h"

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
