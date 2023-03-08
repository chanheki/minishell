#include "../../include/parse.h"

void	join_token_value(t_token **token, char *trimmed_line, int *i)
{
	char	*new_value;
	char	*temp;

	if (!token || !*token)
		*token = create_new_token(NULL, 0);
	else if (!trimmed_line || !trimmed_line[*i])
		return ;
	if (!(*token)->value)
	{
		(*token)->value = ft_strdup(&trimmed_line[*i]);
		return ;
	}
	else
	{
		new_value = ft_strjoin((*token)->value, &trimmed_line[*i]);
		temp = (*token)->value;
		(*token)->value = new_value;
		free(temp);
	}
}
