#include "../../include/parse.h"

char	*get_join_source(char c)
{
	char	*source;

	source = (char *)malloc(sizeof(char) * 2);
	if (!source)
		return (0);
	source[0] = c;
	source[1] = '\0';
	return (source);
}

void	join_token_value(t_token **token, char *trimmed_line, int *i)
{
	char	*new_value;
	char	*temp;
	char	*source;

	if (!token || !*token)
		*token = create_new_token(NULL, 0);
	else if (!trimmed_line || !trimmed_line[*i])
		return ;
	source = get_join_source(trimmed_line[*i]);
	if (!source)
		return ;
	if (!(*token)->value)
	{
		(*token)->value = source;
		return ;
	}
	else
	{
		new_value = ft_strjoin((*token)->value, source);
		temp = (*token)->value;
		(*token)->value = new_value;
		free(temp);
		free(source);
	}
}
