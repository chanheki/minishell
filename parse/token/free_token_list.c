#include "../include/minishell.h"

void	free_token_list(t_token **token)
{
	t_token	*tmp;

	if (!token)
		return ;
	while (*token)
	{
		tmp = *token;
		*token = (*token)->next;
		if (temp->value)
			free(temp->value);
		free(tmp);
	}
}
