#include "../include/minishell.h"

/*
 * Description: 환경 변수의 문자열에서 key를 반환한다.
 * Param.  #1 : 환경 변수의 문자열
 * Return     : 환경 변수의 key
 */
char	*get_env_key(char *env)
{
	int		i;
	char	*key;

	i = 0;
	key = NULL;
	while (env[i] && env[i] != '=')
		i++;
	key = ft_substr(env, 0, i);
	return (key);
}

/*
 * Description: 환경 변수의 문자열에서 value를 반환한다.
 * Param.  #1 : 환경 변수의 문자열
 * Return     : 환경 변수의 value
 */
char	*get_env_value(char *env)
{
	int		i;
	char	*value;

	i = 0;
	value = NULL;
	while (env[i] && env[i] != '=')
		i++;
	value = ft_substr(env, i + 1, ft_strlen(env) - i - 1);
	return (value);
}

/*
 * Description: 환경 변수의 문자열 배열을 환경 변수 딕셔너리로 변환한다.
 * Param.  #1 : 환경 변수의 문자열 배열
 * Return     : SUCCESS: 성공
 *            : ERROR  : 실패
 */
int		cast_env_to_dict(char **env)
{
	int			i;
	char		*key;
	char		*value;
	t_env_dict	*dict;

	i = -1;
	while (env[++i])
	{
		key = get_env_key(env[i]);
		value = get_env_value(env[i]);
		initialize_env_dict(&dict, key, value);
		if (!dict)
			return (ERROR);
		add_to_env_dict(&g_var.env_dict, dict);
	}
	return (SUCCESS);
}
