
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

int	ft_exit(char **argv, int child)
{
	if (!argv || !(*argv))
	{
		printf("ft_exit argument error!\n");
		return (1);
	}
	if (!child)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (is_valid_argument(argv[1]) == false)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(255);
	}
	if (count_argument(argv) > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_var.old_term));
	if (count_argument(argv) == 2)
		exit(ft_atoi(argv[1]));
	exit(g_var.exit_status);
	return (0);
}
