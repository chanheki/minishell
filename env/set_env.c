/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:51:54 by yena              #+#    #+#             */
/*   Updated: 2023/05/15 15:50:42 by yena             ###   ########.fr       */
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
			free(temp->value);
			temp->value = ft_strdup(value);
			if (!temp->value)
				return (ERROR);
			update_envp();
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
	char	*key_equal;

	key_equal = ft_strjoin(key, "=");
	if (!key_equal)
		return (NULL);
	env = ft_strjoin(key_equal, value);
	free(key_equal);
	if (!env)
		return (ft_strdup(key));
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
		if (temp->key && temp->value)
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
		if (temp->key && temp->value)
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

	if (!key && !value)
		return (SUCCESS);
	if (is_already_in(key))
	{
		if (change_env_value(key, value) != SUCCESS)
			return (ERROR);
		if (key)
			free(key);
		if (value)
			free(value);
	}
	else
	{
		initialize_env_dict(&new_dict, key, value);
		if (!new_dict)
			return (ERROR);
		add_to_env_dict(&g_var.env_dict, new_dict);
		update_envp();
	}
	return (SUCCESS);
}
