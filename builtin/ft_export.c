/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:52:27 by yena              #+#    #+#             */
/*   Updated: 2023/05/15 17:12:54 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Description: 유효한 env 키 형식인지 확인한다.
 *              유효한 env 키 형식은 첫 글자가 알파벳인 경우에 해당한다.
 * Param.   #1: env 키를 담고 있는 문자열
 * Return     : 유효하지 않을 경우 exit status가 1임을 나타내는 1을, 유효할 경우 0을 반환한다.
 */
static int	check_env_argv(char *key)
{
	int	i;

	i = -1;
	if (!*key)
	{
		ft_putstr_fd("minishell: export: `=': not a valid identifier\n", \
						STDERR_FILENO);
		free(key);
		key = NULL;
		return (1);
	}
	while (key[++i])
	{
		if (ft_isdigit(key[0]) || !ft_isalnum(*key) || key[i] == BLANK)
		{
			ft_putstr_fd("minishell: export: ", STDERR_FILENO);
			ft_putstr_fd(key, STDERR_FILENO);
			ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
			free(key);
			key = NULL;
			return (1);
		}
	}
	return (0);
}

/*
 * Description: argv에 문자 '='이 있는 경우의 환경변수를 추가한다.
 * Param.   #1: 환경변수를 추가할 문자열
 * Return     : exit status를 반환한다.
 */
int	ft_export_with_equal(char *argv)
{
	char	*argv_dup;

	argv_dup = ft_strdup(argv);
	if (check_env_argv(argv_dup))
		return (1);
	free(argv_dup);
	argv_dup = NULL;
	if (is_already_in(argv))
		return (0);
	if (set_env(ft_strdup(argv), NULL) != SUCCESS)
		return (1);
	return (0);
}

/*
 * Description: 환경변수를 추가한다.
 * Param.   #1: 환경변수를 추가할 문자열
 * Return     : exit status를 반환한다.
 */
int	ft_export(char **argv)
{
	char	*key;
	char	*value;
	int		i;
	int		exit_status;

	i = 0;
	exit_status = 0;
	if (!argv[1])
		return (print_envp());
	while (argv[++i])
	{
		if (!ft_strchr(argv[i], '='))
		{
			ft_export_with_equal(argv[i]);
			continue ;
		}
		key = get_env_key(argv[i]);
		exit_status = check_env_argv(key);
		if (exit_status)
			continue ;
		value = get_env_value(argv[i]);
		if (set_env(key, value) != SUCCESS)
			exit_status = 1;
	}
	return (exit_status);
}
