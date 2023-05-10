/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_token_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:54:17 by yena              #+#    #+#             */
/*   Updated: 2023/05/10 20:54:18 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Description: join 에 필요한 문자를 문자열로 만든다.
 * Param:       char c: 문자
 * Return:      char *: 문자열
 */
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

/*
 * Description: 기존 토큰의 value에 새로운 문자를 추가한다.
 * Param.   #1: 토큰 리스트의 주소
 * Param.   #2: 토큰화 할 문자열(= 커맨드 라인)
 * Param.   #3: 커맨드 라인에서 몇 번째 글자인지를 나타내는 인덱스 포인터
 * Return:      없음
 */
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
