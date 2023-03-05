#include "../../include/minishell.h"

void	join_token_value(t_token **token, char *trimmed_line, int *i)
{
	char	*new_value;
	char	*temp;

	if (!token || !*token)
		token = create_new_token(ft_strdup(trimmed_line[*i]));
	else
	{
		new_value = ft_strjoin(*token->value, &trimmed_line[*i]);
		temp = *token->value;
		*token->value = new_value;
		free(temp);
	}
}
