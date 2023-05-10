#include "../../include/minishell.h"

/*
 * Description: 키에 해당하는 값을 환경변수를 딕셔너리에서 지운다.
 * Param.   #1: 환경 변수 딕셔너리의 키
 * Return     : 없음
 */
void	delete_env(char *key)
{
	t_env_dict	*temp;
	t_env_dict	*next;

	if (!g_var.env_dict)
		return ;
	temp = g_var.env_dict;
	while (temp)
	{
		next = temp->next;
		if (!ft_strcmp(temp->key, key))
		{
			if (!temp->prev)
				g_var.env_dict = next;
			free_one_env_dict(temp);
		}
		temp = next;
	}
	update_envp();
}
