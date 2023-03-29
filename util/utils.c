
#include "../include/minishell.h"

int	check_token_type_operator(t_token *token)
{
	if (token == NULL || token->value == NULL)
		return (false);
	if (token->type == DAMPERSAND || token->type == DPIPE)
		return (true);
	return (false);
}

int	token_typecheck(t_token *token, t_token_type type)
{
	if (token == NULL || token->value == NULL)
		return (false);
	if (token->type == (t_token_type)(type))
		return (true);
	return (false);
}