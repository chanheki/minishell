#include "../../include/minishell.h"

t_token	*get_tail_token(t_token **token)
{
	t_token	*tmp;

	if (!*token)
		return (NULL);
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
