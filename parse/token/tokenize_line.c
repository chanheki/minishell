#include "../../include/parse.h"

t_token	*tokenize_line(char *trimmed_line)
{
	t_token	*token;
	t_token	*new_token;
	int		i;

	if (!*trimmed_line)
		return (NULL);
	i = 0;
	token = NULL;
	while (trimmed_line[i])
	{
		// TODO => ls ''-al(= -al로), ls -al ' '(에러) 처리 해야 함
		new_token = create_new_token(NULL, 0);
		if (!new_token)
		{
			free_token_list(&token);
			return (NULL);
		}
		set_token(new_token, trimmed_line, &i);
		while (trimmed_line[i] && trimmed_line[i] == SPACE)
			i++;
		add_token_to_tail(&token, new_token);
	}
	return (token);
}
