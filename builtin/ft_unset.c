/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:52:22 by yena              #+#    #+#             */
/*   Updated: 2023/05/15 16:53:25 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Description: 유효한 env 키 형식인지 확인한다.
 *              유효한 env 키 형식은 첫 글자가 알파벳인 경우에 해당한다.
 * Param.   #1: env 키를 담고 있는 문자열
 * Return     : 유효하지 않을 경우 exit status가 1임을 나타내는 1을, 유효할 경우 0을 반환한다.
 */
static int	check_env_argv(char *argv)
{
	if (!((*argv >= 'A' && *argv <= 'Z')
			|| (*argv >= 'a' && *argv <= 'z')))
	{
		ft_putstr_fd("minishell: unset: ", STDERR_FILENO);
		ft_putstr_fd(argv, STDERR_FILENO);
		ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

/*
 * Description: 주어진 문자열들을 키로 하는 env 값을 지운다.
 * Param.   #1: 'unset'을 포함하여 env 키들을 담고 있는 문자열 포인터
 * Return     : 에러가 있었을 경우 1을, 모두 성공적으로 실행했을 경우 0을 반환한다.
 */
int	ft_unset(char **argv)
{
	int		i;
	int		exit_status;

	i = 0;
	exit_status = 0;
	while (argv[++i])
	{
		if (check_env_argv(argv[i]))
		{
			exit_status = 1;
			continue ;
		}
		if (is_already_in(argv[i]))
			delete_env(argv[i]);
	}
	return (exit_status);
}
