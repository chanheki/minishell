#include "../include/minishell.h"

/*
 * Description: key에 맞는 환경변수의 value를 변경한다.
 * Param.   #1: 변경할 환경변수의 키
 * Param.   #2: 변경할 환경변수의 값
 * Return     : SUCCESS: 성공
 *            : ERROR  : 실패
 */
int	change_env_value(char *key, char *value)
{
	t_env_dict	*temp;

	temp = g_var.env_dict;
	while (temp)
	{
		if (!ft_strcmp(temp->key, key))
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			if (!temp->value)
				return (ERROR);
			return (SUCCESS);
		}
		temp = temp->next;
	}
	return (ERROR);
}

/*
 * Description: g_var.envp를 업데이트한다.
 * Param.     : 없음
 * Return     : 없음
 */
void	update_envp(void)
{
	int			i;
	t_env_dict	*temp;
	char		**envp;

	i = 0;
	temp = g_var.env_dict;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return ;
	i = -1;
	temp = g_var.env_dict;
	while (temp)
	{
		envp[++i] = ft_strjoin(temp->key, temp->value);
		temp = temp->next;
	}
	envp[i] = NULL;
	ft_split_free(g_var.envp);
	g_var.envp = envp;
}

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
		if (change_env_value(key, value) != SUCCESS)
			return (ERROR);
	}
	else
	{
		initialize_env_dict(&new_dict, key, value);
		if (!new_dict)
			return (ERROR);
		add_to_env_dict(&g_var.env_dict, new_dict);
	}
	return (SUCCESS);
}