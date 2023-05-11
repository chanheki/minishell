/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens_in_parenthesis.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:54:07 by yena              #+#    #+#             */
/*   Updated: 2023/05/11 09:34:14 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Description: 열린 괄호 다음부터 닫힌 괄호 전까지의 토큰을 복제한다.
 * Param.   #1: 열린 괄호 토큰의 주소
 * Param.   #2: 닫힌 괄호 토큰의 주소
 * Return     : 복제한 토큰 리스트의 첫 번째 요소의 주소
 */
t_token	*get_tokens_in_parenthesis(t_token *open, t_token *close)
{
	t_token	*tokens_in_parent;
	t_token	*new_token;
	t_token	*temp;

	temp = open->next;
	tokens_in_parent = NULL;
	while (temp->next && temp != close)
	{
		if (ft_strnstr(temp->value, "exit", ft_strlen(temp->value)))
			return (NULL);
		if (!tokens_in_parent)
			tokens_in_parent = create_new_token(ft_strdup(temp->value),
					temp->type);
		else
		{
			new_token = create_new_token(ft_strdup(temp->value), temp->type);
			add_token_to_tail(&tokens_in_parent, new_token);
		}
		temp = temp->next;
	}
	if (temp != close)
		free_token_list(&tokens_in_parent);
	return (tokens_in_parent);
}
