/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_to_tail.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:53:45 by yena              #+#    #+#             */
/*   Updated: 2023/05/10 20:53:46 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Description: 토큰을 토큰 리스트의 맨 끝에 추가한다.
 * Param.   #1: 토큰 리스트
 * Param.   #2: 추가할 토큰
 * Return     : 없음
 */
void	add_token_to_tail(t_token **token, t_token *new)
{
	t_token	*tail;

	if (!token && !new)
		return ;
	else if (!*token && new)
	{
		*token = new;
		return ;
	}
	tail = get_tail_token(token);
	tail->next = new;
	new->prev = tail;
}
