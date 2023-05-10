/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:52:25 by yena              #+#    #+#             */
/*   Updated: 2023/05/10 21:18:04 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Description: 현재 디렉토리 경로를 출력한다.
 * Param.     : 없음
 * Return     : 성공하면 0, 실패하면 1을 반환한다.
 */
int	ft_pwd(void)
{
	size_t	size;
	char	*working_dir;

	size = 1024;
	working_dir = (char *)malloc(sizeof(char) * (size + 1));
	working_dir[size] = '\0';
	if (getcwd(working_dir, size))
	{
		ft_putstr_fd(working_dir, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(working_dir);
		working_dir = NULL;
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell: pwd: can't find current working directory\n",
			STDERR_FILENO);
		return (1);
	}
}
