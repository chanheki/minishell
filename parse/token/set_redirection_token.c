#include "../../include/parse.h"

void	set_redirection_token(t_token **token, char *trimmed_line, int *i)
{
	while (trimmed_line[*i] && ft_isdigit(trimmed_line[*i]))
	{
		join_token_value(token, trimmed_line, i);
		(*i)++;
	}
	if (trimmed_line[*i] && trimmed_line[*i] != SPACE)
	{
		if (ft_strchr("<>", trimmed_line[*i]))
			set_operator_token(token, trimmed_line, i);
		else if (ft_strchr("();&|", trimmed_line[*i]))
			return ;
		else
			set_normal_token(token, trimmed_line, i);
	}
}
