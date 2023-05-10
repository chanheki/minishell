/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 03:13:03 by chanheki          #+#    #+#             */
/*   Updated: 2023/05/11 03:13:07 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_isinteger(char *str)
{
	int		n;
	char	*res;

	n = ft_atoi(str);
	res = ft_itoa(n);
	if (!res)
		return (0);
	if (ft_strcmp(str, res) != 0)
	{
		free(res);
		return (0);
	}
	free(res);
	return (1);
}

static bool	is_valid_argument(char *arg)
{
	if (!arg)
		return (true);
	return (ft_isinteger(arg));
}

static int	count_argument(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	ft_exit(char **argv, t_process_type type)
{
	if (!argv || !(*argv))
	{
		ft_putendl_fd("Jip-Shell: ft_exit argv error \n", STDERR_FILENO);
		return (EXIT_BUILT_IN_FAIL);
	}
	jipshell_will_terminate();
	if (type == P_PARENT)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (is_valid_argument(argv[1]) == false)
	{
		ft_putstr_fd("Jip-S ell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(EXIT_OUT_OF_RANGE);
	}
	if (count_argument(argv) > 2)
	{
		ft_putendl_fd("Jip-Shell: exit: too many arguments", STDERR_FILENO);
		exit(EXIT_TOO_MANY_ARGUMENTS);
	}
	if (count_argument(argv) == 2)
		exit(ft_atoi(argv[1]));
	exit(g_var.exit_status);
	return (0);
}
