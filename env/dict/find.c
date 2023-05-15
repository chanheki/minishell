/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 21:19:22 by yena              #+#    #+#             */
/*   Updated: 2023/05/15 14:40:58 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Description: 키에 해당하는 값을 환경변수 딕셔너리에서 가져온다
 * Param.   #1: 환경 변수 딕셔너리의 키
 * Return     : 환경 변수 딕셔너리의 값
 */
char	*find_value(char *key)
{
	t_env_dict	*temp;

	temp = g_var.env_dict;
	while (temp)
	{
		if (!ft_strcmp(temp->key, key))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

/*
 * Description: 환경변수에 이미 해당하는 키가 존재하는지 확인한다.
 * Param.   #1: 환경 변수 딕셔너리의 키
 * Return     : true : 존재하는 키
 *            : false: 키가 존재하지 않음
 */
bool	is_already_in(char *key)
{
	t_env_dict	*temp;

	temp = g_var.env_dict;
	while (temp)
	{
		if (!ft_strcmp(temp->key, key))
			return (true);
		temp = temp->next;
	}
	return (false);
}
