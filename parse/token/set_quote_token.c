#include "../../include/minishell.h"

void	set_single_quote_token(t_token **token, char *trimmed_line, int *i)
{
	while (trimmed_line[*i])
	{
		join_token_value(token, trimmed_line, i);
		if (trimmed_line[*i] == QUOTE)
		{
			(*token)->status = IN_NORMAL;
			(*i)++;
			set_token(token, trimmed_line, i);
		}
		(*i)++;
	}
}

void	set_double_quote_token(t_token **token, char *trimmed_line, int *i)
{
	while (trimmed_line[*i])
	{
		join_token_value(token, trimmed_line, i);
		(*token)->status = IN_DQUOTE;
		if ((*token)->status != IN_ESCAPE && trimmed_line[*i] == ESCAPE)
		{
			(*token)->status = IN_ESCAPE;
			(*i)++;
			continue ;
		}
		else if (trimmed_line[*i] == DQUOTE)
		{
			(*token)->status = IN_NORMAL;
			(*i)++;
			set_token(token, trimmed_line, i);
			return ;
		}
		(*i)++;
	}
}

void	set_quote_token(t_token **token, char *trimmed_line, int *i)
{
	join_token_value(token, trimmed_line, i);
	if (trimmed_line[*i] == QUOTE)
	{
		(*i)++;
		(*token)->status = IN_QUOTE;
		set_single_quote_token(token, trimmed_line, i);
	}
	else if (trimmed_line[*i] == DQUOTE)
	{
		(*i)++;
		(*token)->status = IN_DQUOTE;
		set_double_quote_token(token, trimmed_line, i);
	}
}
