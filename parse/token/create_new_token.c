#include "../../include/parse.h"

/*
 * Description: 새로운 토큰을 만든다.
 * Param.   #1: 토큰의 값을 가리키는 char *.
 * Param.   #2: 토큰의 타입을 나타내는 enum e_token_type.
 * Return     : 새로 만들어진 토큰
 */
t_token	*create_new_token(void *value, enum e_token_type type)
{
	t_token		*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->value = value;
	new_token->type = type;
	new_token->is_in_quote = false;
	new_token->is_in_dquote = false;
	new_token->is_in_escape = false;
	new_token->next = NULL;
	return (new_token);
}
