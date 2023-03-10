#include "../../include/parse.h"

enum e_token_type	get_operator_token_type(char c)
{
	if (c == '(')
		return (PARENTHESIS_OPEN);
	else if (c == ')')
		return (PARENTHESIS_CLOSE);
	else if (c == ';')
		return (SEMICOLON);
	else if (c == '&')
		return (AMPERSAND);
	else if (c == '<')
		return (REDIRECT_IN);
	else if (c == '>')
		return (REDIRECT_OUT);
	else if (c == '|')
		return (PIPE);
	else
		return (NORMAL);
}

enum e_token_type	get_double_operator_token_type(char c)
{
	if (c == '&')
		return (DAMPERSAND);
	else if (c == '<')
		return (DREDIRECT_IN);
	else if (c == '>')
		return (DREDIRECT_OUT);
	else if (c == '|')
		return (DPIPE);
	else
		return (NORMAL);
}

void	set_operator_token(t_token **token, char *trimmed_line, int *i)
{
	char	*operator;

	if ((*token)->value)
		return ;
	operator = &trimmed_line[*i];
	if (ft_strchr("();", *operator))
	{
		join_token_value(token, trimmed_line, i);
		(*token)->type = get_operator_token_type(*operator);
		(*i)++;
	}
	else if (ft_strchr("<>&|", trimmed_line[*i]))
	{
		while (trimmed_line[*i] == *operator)
		{
			join_token_value(token, trimmed_line, i);
			(*i)++;
		}
		if ((&trimmed_line[*i] - operator) == 2)
			(*token)->type = get_double_operator_token_type(*operator);
		else
			(*token)->type = get_operator_token_type(*operator);
	}
}
