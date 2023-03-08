#include "../../include/parse.h"

void	join_token_value(t_token **token, char *trimmed_line, int *i)
{
	char	*new_value;
	char	*temp;
	char	c;

	if (!token || !*token)
		*token = create_new_token(NULL, 0);
	else if (!trimmed_line || !trimmed_line[*i])
		return ;
	c = trimmed_line[*i];
	if (!(*token)->value)
	{
		(*token)->value = ft_strdup(&c);
		return ;
	}
	else
	{
		new_value = ft_strjoin((*token)->value, &c);
		temp = (*token)->value;
		(*token)->value = new_value;
		free(temp);
	}
}
