/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tail_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:54:05 by yena              #+#    #+#             */
/*   Updated: 2023/05/10 20:54:05 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*get_tail_token(t_token **token)
{
	t_token	*tmp;

	if (!*token)
		return (NULL);
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
