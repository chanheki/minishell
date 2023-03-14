#include "../../include/parse.h"

void	set_token(t_token *token, char *trimmed_line, int *i)
{
	if (trimmed_line[*i] == ESCAPE)
		set_normal_token(&token, trimmed_line, i);
	else if (trimmed_line[*i] == QUOTE || trimmed_line[*i] == DQUOTE)
		set_quote_token(&token, trimmed_line, i);
	else if (ft_strchr("<>()|;&", trimmed_line[*i]))
		set_operator_token(&token, trimmed_line, i);
	else if (ft_isdigit(trimmed_line[*i]))
		set_fd_redirection_token(&token, trimmed_line, i);
	else
		set_normal_token(&token, trimmed_line, i);
}
