#include "libft.h"

t_token	*create_new_token(void *value, enum e_token_type type)
{
	t_token		*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->value = value;
	new_token->type = type;
	new_token->is_in_quotes = false;
	new_token->is_in_dquotes = false;
	new_token->is_in_parentesis = false;
	new_token->is_in_escape = false;
	new_token->next = NULL;
	return (new_token);
}
