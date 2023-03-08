#include "../../include/parse.h"

void	set_single_quote_token(t_token **token, char *trimmed_line, int *i)
{
	while (trimmed_line[*i] && trimmed_line[*i] != QUOTE)
	{
		join_token_value(token, trimmed_line, i);
		(*i)++;
	}
	join_token_value(token, trimmed_line, i);
	(*token)->is_in_quote = false;
	(*i)++;
	set_token(*token, trimmed_line, i);
}

void	set_double_quote_token(t_token **token, char *trimmed_line, int *i)
{
	while (trimmed_line[*i] && trimmed_line[*i] != DQUOTE)
	{
		join_token_value(token, trimmed_line, i);
		if (!((*token)->is_in_escape) && trimmed_line[*i] == ESCAPE)
			(*token)->is_in_escape = true;
		(*i)++;
	}
	join_token_value(token, trimmed_line, i);
	(*token)->is_in_dquote = false;
	(*i)++;
	set_token(*token, trimmed_line, i);
	return ;
}

void	set_quote_token(t_token **token, char *trimmed_line, int *i)
{
	join_token_value(token, trimmed_line, i);
	if (trimmed_line[*i] == QUOTE)
	{
		(*i)++;
		(*token)->is_in_quote = true;
		set_single_quote_token(token, trimmed_line, i);
	}
	else if (trimmed_line[*i] == DQUOTE)
	{
		(*i)++;
		(*token)->is_in_dquote = true;
		set_double_quote_token(token, trimmed_line, i);
	}
}
