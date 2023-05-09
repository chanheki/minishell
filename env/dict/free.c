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
	free(dict->key);
	dict->key = NULL;
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