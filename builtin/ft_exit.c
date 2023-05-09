
// exit with no options

// 　옵션이 없는 exit

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
		exit(255);
	}
	if (count_argument(argv) > 2)
	{
		ft_putendl_fd("Jip-Shell: exit: too many arguments", STDERR_FILENO);
		exit(1);
	}
	if (count_argument(argv) == 2)
		exit(ft_atoi(argv[1]));
	return (0);
}
