#include "../../include/parse.h"

t_token	*tokenize_line(char *trimmed_line)
{
	t_token	*token;
	t_token	*new_token;
	int		i;

	if (!*trimmed_line)
		return (NULL);
	i = 0;
	while (trimmed_line[i])
	{
		new_token = create_new_token(NULL, NULL);
		if (!new_token)
		{
			free_token_list(&token);
			return (NULL);
		}
		set_token(new_token, trimmed_line, i);
		add_token_to_tail(&token, new_token);
	}
	return (token);
}
