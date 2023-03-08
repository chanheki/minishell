#include "../../include/parse.h"

void	free_token_list(t_token **token)
{
	t_token	*temp;

	if (!token)
		return ;
	while (*token)
	{
		temp = *token;
		*token = (*token)->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}
