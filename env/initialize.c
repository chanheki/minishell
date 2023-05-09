#include "../include/minishell.h"

int	initialize_env(char **env)
{
}

/*
 * Description: 환경 변수 딕셔너리를 초기화한다.
 * Param.   #1: 딕셔너리
 * Param.   #2: 딕셔너리의 키
 * Param.   #3: 딕셔너리의 값
 * Return     : 없음
 */
void	initialize_env_dict(t_env_dict **dict, char *key, char *value)
{
	*dict = (t_env_dict *)malloc(sizeof(t_env_dict));
	if (!*dict)
		return ;
	(*dict)->key = key;
	(*dict)->value = value;
	(*dict)->next = NULL;
	(*dict)->prev = NULL;
}
