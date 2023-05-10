/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:54:35 by yena              #+#    #+#             */
/*   Updated: 2023/05/11 00:19:55 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Description: 토큰의 타입에 따라 토큰을 생성한다.
 * Param.   #1: 토큰 리스트의 주소를 가리키는 포인터의 주소
 * Param.   #2: 토큰에 들어갈 값
 * Param.   #3: 커맨드 라인에서 몇 번째 글자인지를 나타내는 인덱스 포인터
 * Return     : 없음
 */
void	set_token(t_token **token, char *trimmed_line, int *i)
{
	if (trimmed_line[*i] == ESCAPE)
		set_normal_token(token, trimmed_line, i);
	else if (is_quote(trimmed_line[*i]))
		set_quote_token(token, trimmed_line, i);
	else if (ft_strchr("<>()|&", trimmed_line[*i]))
		set_operator_token(token, trimmed_line, i);
	else if (ft_isdigit(trimmed_line[*i]))
		set_fd_redirection_token(token, trimmed_line, i);
	else
	{
		set_normal_token(token, trimmed_line, i);
		if (!(*token)->value)
		{
			if ((*token)->prev || (*token)->next)
				free_token(token);
			return ;
		}
		if (ft_strchr((*token)->value, WILDCARD)
			&& ((*token)->prev && (*token)->prev->type != DREDIRECT_IN))
			(*token)->type = WILDCARD;
	}
}
