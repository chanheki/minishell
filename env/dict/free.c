/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:52:17 by yena              #+#    #+#             */
/*   Updated: 2023/05/15 16:53:12 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Description: 환경 변수 딕셔너리 한 개를 할당 해제한다.
 * Param.   #1: 환경 변수 딕셔너리
 * Return     : 없음
 */
void	free_one_env_dict(t_env_dict *dict)
{
	if (!dict)
		return ;
	if (dict->prev)
	{
		if (dict->next)
			dict->prev->next = dict->next;
		else
			dict->prev->next = NULL;
	}
	if (dict->next)
	{
		if (dict->prev)
			dict->next->prev = dict->prev;
		else
			dict->next->prev = NULL;
	}
	if (dict->key)
		free(dict->key);
	dict->key = NULL;
	if (dict->value)
		free(dict->value);
	dict->value = NULL;
	free(dict);
	dict = NULL;
}

/*
 * Description: 환경 변수 딕셔너리를 할당 해제한다.
 * Param.   #1: 환경 변수 딕셔너리
 * Return     : 없음
 */
void	free_env_dict(t_env_dict *dict)
{
	t_env_dict	*tmp;

	while (dict)
	{
		tmp = dict->next;
		free_one_env_dict(dict);
		dict = tmp;
	}
}
