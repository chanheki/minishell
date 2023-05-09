#include "../include/minishell.h"

/*
 * Description: 환경 변수 문자열 배열을 g_var 내 env에 저장한다.
 * Param.   #1: 환경 변수 문자열 배열
 * Return     : SUCCESS: 성공
 *            : ERROR  : 실패
 */
int	initialize_env(char **env)
{
	g_var.env_dict = NULL;
	if (cast_env_to_dict(env) == ERROR)
		return (ERROR);
	return (SUCCESS);
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
