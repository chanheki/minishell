/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:53:54 by yena              #+#    #+#             */
/*   Updated: 2023/05/11 11:39:04 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Description: 토큰의 메모리를 해제한다.
 * Param      : 해제할 토큰
 * Return     : void
 */
void	free_token(t_token **token)
{
	if (!token || !*token)
		return ;
	if ((*token)->prev)
	{
		if ((*token)->next)
			(*token)->prev->next = (*token)->next;
		else
			(*token)->prev->next = NULL;
	}
	if ((*token)->next)
	{
		if ((*token)->prev)
			(*token)->next->prev = (*token)->prev;
		else
			(*token)->next->prev = NULL;
	}
	if ((*token)->value)
	{
		free((*token)->value);
		(*token)->value = NULL;
	}
	free(*token);
	*token = NULL;
}

/*
 * Description: 토큰 리스트의 메모리를 해제한다.
 * Param      : 해제할 토큰 리스트
 * Return     : void
 */
void	free_token_list(t_token **token)
{
	t_token	*temp;

	if (!token)
		return ;
	*token = get_head_token(*token);
	while (*token)
	{
		temp = (*token)->next;
		free_token(token);
		*token = temp;
	}
	*token = NULL;
}
