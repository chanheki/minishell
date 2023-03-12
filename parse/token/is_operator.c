#include "../../include/parse.h"

bool	is_operator(t_token *token)
{
	if (token->type == PIPE
		|| token->type == DAMPERSAND || token->type == DPIPE)
		return (true);
	return (false);
}
