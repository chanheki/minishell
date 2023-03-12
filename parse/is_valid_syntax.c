#include "../include/parse.h"

bool	is_pair_of_parenthesis(t_token *token, char **token_value)
{
	t_token	*temp;
	int 	parenthesis_count;

	parenthesis_count = 0;
	temp = token;
	while (temp)
	{
		*token_value = temp->value;
		if (temp->type == PARENTHESIS_OPEN)
			parenthesis_count++;
		else if (temp->type == PARENTHESIS_CLOSE)
			parenthesis_count--;
		if (parenthesis_count < 0)
			return (false);
		temp = temp->next;
	}
	if (parenthesis_count == 0)
		return (true);
	return (false);
}

bool	is_valid_redirection(t_token *token, char **token_value)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		*token_value = temp->value;
		if (temp->type == REDIRECT_IN || temp->type == REDIRECT_OUT
			|| temp->type == DREDIRECT_IN || temp->type == DREDIRECT_OUT)
		{
			temp = temp->next;
			if (!temp || temp->type != NORMAL)
				return (false);
		}
		temp = temp->next;
	}
	return (true);
}

t_token	*get_last_token_in_parenthesis(t_token **token)
{
	t_token	*temp;
	int		parenthesis_count;

	if (!token || !*token)
		return (NULL);
	parenthesis_count = 1;
	temp = *token;
	while (temp->next)
	{
		if (temp->next->type == PARENTHESIS_OPEN)
			parenthesis_count++;
		else if (temp->next->type == PARENTHESIS_CLOSE)
			parenthesis_count--;
		if (parenthesis_count == 0)
			break ;
		temp = temp->next;
	}
	if (!temp->next)
		return (NULL);
	if (temp->type == PARENTHESIS_OPEN || temp->type == PARENTHESIS_CLOSE)
	{
		*token = temp;
		return (NULL);
	}
	return (temp);
}

bool	is_valid_parenthesis(t_token *token, char **token_value)
{
	t_token	*prev;
	t_token *next;
	t_token *temp;

	prev = NULL;
	temp = token;
	while (temp)
	{
		*token_value = temp->value;
		if (temp->type == PARENTHESIS_OPEN)
		{
			temp = temp->next;
			next = get_last_token_in_parenthesis(&temp);
			if (!next)
				return (false);
			next = next->next->next;
			if ((!prev || prev->type == AMPERSAND || prev->type == PIPE)
				&& (!next || next->type == AMPERSAND || next->type == PIPE))
				return (false);
		}
		prev = temp;
		temp = temp->next;
	}
	return (true);
}

bool	is_valid_command(t_token *token, char **token_value)
{
	t_token	*temp;
	bool 	is_in_normal;

	temp = token;
	is_in_normal = false;
	while (temp)
	{
		*token_value = temp->value;
		if (temp->type == AMPERSAND || temp->type == PIPE)
		{
			if (!is_in_normal)
				return (false);
			is_in_normal = false;
		}
		else if (temp->type == NORMAL)
			is_in_normal = true;
		else if (temp->type == REDIRECT_IN || temp->type == REDIRECT_OUT
			|| temp->type == DREDIRECT_IN || temp->type == DREDIRECT_OUT)
			temp = temp->next;
		temp = temp->next;
	}
	return (true);
}

bool	is_valid_syntax(t_token *token)
{
	char	*token_value;

	if (!is_pair_of_parenthesis(token, &token_value)
		|| !is_valid_parenthesis(token, &token_value)
		|| !is_valid_redirection(token, &token_value))
	{
		ft_putstr_fd("JIP-shell: syntax error near unexpected token `", 2);
		ft_putstr_fd(token_value, 2);
		ft_putendl_fd("'", 2);
		return (false);
	}
	else if (!is_valid_command(token, &token_value))
	{
		ft_putstr_fd("JIP-shell: command not found: ", 2);
		ft_putendl_fd(token_value, 2);
		return (false);
	}
	return (true);
}
