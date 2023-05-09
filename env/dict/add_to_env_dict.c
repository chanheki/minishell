#include "../../include/minishell.h"

/*
 * Description: 환경 변수 딕셔너리에 새로운 환경 변수를 추가한다.
 * Param.  #1 : 환경 변수 딕셔너리
 * Param.  #2 : 새로운 환경 변수
 * Return     : 없음
 */
void	add_to_env_dict(t_env_dict *dict, t_env_dict *new_dict)
{
	t_env_dict	*tmp;

	if (!new_dict)
		return ;
	if (!dict)
	{
		dict = new_dict;
		return ;
	}
	tmp = dict;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_dict;
	new_dict->prev = tmp;
}
