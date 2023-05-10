/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 04:57:33 by chanheki          #+#    #+#             */
/*   Updated: 2023/05/11 05:28:32 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Description: is_valid_option
 *            : 유효한 옵션인지 확인한다.
 * Param.   #1: *str
 */
static bool	is_valid_option(char *str)
{
	int	i;

	if (!str || *str != '-' || str[1] != 'n')
		return (false);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

/*
 * Description: print_argument
 *            : option -n옵션을 고려하여 구현
 * Param.   #1: **option
 * Param.   #2: start_idx
 */
static void	print_argument(char **option, int start_idx)
{
	int	i;

	i = start_idx;
	while (option[i])
	{
		if (i != start_idx)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(option[i], STDOUT_FILENO);
		i++;
	}
}

/*
 * Description: ft_echo
 *            : 쉘 내장 함수인 echo를 구현한다. -n 옵션 가능.
 * Param.   #1: **option
 * Return     : exit code 0 / ERROR
 */
int	ft_echo(char **option)
{
	int	i;

	i = 1;
	if (!option || !(*option))
	{
		ft_putstr_fd("ft_echo argument error!\n", 2);
		return (1);
	}
	while (is_valid_option(option[i]) == true)
	{
		i++;
	}
	if (is_valid_option(option[1]) == false)
	{
		print_argument(option, 1);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else
	{
		print_argument(option, i);
	}
	return (0);
}
