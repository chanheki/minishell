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
