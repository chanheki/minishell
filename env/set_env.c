#include "../include/minishell.h"

/*
 * Description: 환경변수를 추가한다.
 * Param.   #1: 추가할 환경변수의 키
 * Param.   #2: 추가할 환경변수의 값
 * Return     : SUCCESS: 성공
 *            : ERROR  : 실패
 */
int	set_env(char *key, char *value)
{
	t_env_dict	*new_dict;

	if (find_value(key))
	{
		if (change_value(key, value) != SUCCESS)
			return (ERROR);
	}
	else
	{
		initialize_env_dict(&new_dict, key, value);
		if (!new_dict)
			return (ERROR);
		add_to_env_dict(&g_var.env_dict, new_dict);
	}
	update_envp();
	return (SUCCESS);
}