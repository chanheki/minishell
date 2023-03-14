#include "../../include/parse.h"

t_token	*get_last_token_in_parenthesis(t_token **token)
{
	t_token	*temp;
	int		parenthesis_count;

	if (!token || !*token)
		return (NULL);
	parenthesis_count = 1;
	temp = *token;
	while (temp->next)
	{
		if (temp->next->type == PARENTHESIS_OPEN)
			parenthesis_count++;
		else if (temp->next->type == PARENTHESIS_CLOSE)
			parenthesis_count--;
		if (parenthesis_count == 0)
			break ;
		temp = temp->next;
	}
	if (!temp->next)
		return (NULL);
	if (temp->type == PARENTHESIS_OPEN || temp->type == PARENTHESIS_CLOSE)
	{
		*token = temp;
		return (NULL);
	}
	return (temp);
}
