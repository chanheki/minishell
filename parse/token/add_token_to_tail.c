#include "../../include/parse.h"

void	add_token_to_tail(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!token && !new)
		return ;
	else if (!*token && new)
	{
		*token = new;
		return ;
	}
	tmp = get_tail_token(token);
	tmp->next = new;
}
