/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:51:54 by yena              #+#    #+#             */
/*   Updated: 2023/05/14 13:37:31 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			delete_env(key);
			if (set_env(key, value) == ERROR)
				return (ERROR);
			return (SUCCESS);
		}
		temp = temp->next;
	}
	return (ERROR);
}

/*
 * Description: 환경변수의 키, '=', 값를 합쳐 문자열을 만든다.
 * Param.   #1: 환경변수의 키
 * Param.   #2: 환경변수의 값
 * Return     : 환경변수의 문자열
 */

char	*create_env_string(char *key, char *value)
{
	char	*env;
	char	*temp;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	env = ft_strjoin(temp, value);
	free(temp);
	return (env);
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
		envp[++i] = create_env_string(temp->key, temp->value);
		temp = temp->next;
	}
	envp[i + 1] = NULL;
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

	if (!key || !value)
	{
		if (key && *key)
			free(key);
		if (value && *value)
			free(value);
		return (SUCCESS);
	}
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
	update_envp();
	return (SUCCESS);
}
