#include "libft.h"

t_token	*create_new_token(void *value, enum e_token_type type,
		enum e_token_status status)
{
	t_token		*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->value = value;
	new_token->type = type;
	new_token->status = status;
	new_token->next = NULL;
	return (new_token);
}
