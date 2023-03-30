#include "../../include/minishell.h"

/*
 * Description: 앞 뒤 공백이 잘린 문자열을 토큰화한다.
 *              set_token() 함수를 호출하여 반환된 토큰을 토큰 리스트의 뒤에 추가한다.
 * Param.   #1: 앞 뒤 공백이 잘린 문자열
 * Return     : 토큰화된 토큰 리스트
 */
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
		new_token = create_new_token(NULL, NORMAL);
		if (!new_token)
		{
			free_token_list(&token);
			return (NULL);
		}
		add_token_to_tail(&token, new_token);
		set_token(&new_token, trimmed_line, &i);
		token = new_token;
		while (trimmed_line[i] && trimmed_line[i] == BLANK)
			i++;
	}
	return (get_head_token(&token));
}
