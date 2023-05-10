/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_head_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:53:57 by yena              #+#    #+#             */
/*   Updated: 2023/05/11 00:12:18 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Description: 토큰 리스트의 맨 앞 토큰을 반환한다.
 * Param.  #1 : 토큰 리스트
 * Return     : 토큰 리스트의 맨 앞 토큰
 */
t_token	*get_head_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->prev)
		token = token->prev;
	return (token);
}
