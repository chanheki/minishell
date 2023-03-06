#include "../../include/parse.h"

void	set_normal_token(t_token **token, char *trimmed_line, int *i)
{
	while (trimmed_line[*i] && trimmed_line[*i] != SPACE)
	{
		if (trimmed_line[*i] == QUOTE || trimmed_line[*i] == DQUOTE)
		{
			set_quote_token(token, trimmed_line, i);
			continue ;
		}
		else if (ft_strchr("<>()|;&", trimmed_line[*i]))
			return ;
		else if (*token->status != IN_ESCAPE && trimmed_line[*i] == ESCAPE)
		{
			*token->status = IN_ESCAPE;
			join_token_value(token, trimmed_line, i);
			(*i)++;
			continue ;
		}
		*token->status = IN_NORMAL;
		join_token_value(token, trimmed_line, i);
		(*i)++;
	}
}
