#include "../../include/minishell.h"

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
		free(dict->key);
		dict->key = NULL;
		free(dict->value);
		dict->value = NULL;
		free(dict);
		dict = tmp;
	}
}