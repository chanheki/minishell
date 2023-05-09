
// // exit with no options

// // 　옵션이 없는 exit

// #include "../include/minishell.h"

// static int	ft_isinteger(char *str)
// {
// 	int		n;
// 	char	*res;

// 	n = ft_atoi(str);
// 	res = ft_itoa(n);
// 	if (!res)
// 		return (0);
// 	if (ft_strcmp(str, res) != 0)
// 	{
// 		free(res);
// 		return (0);
// 	}
// 	free(res);
// 	return (1);
// }

// static bool	is_valid_argument(char *arg)
// {
// 	if (!arg)
// 		return (true);
// 	return (ft_isinteger(arg));
// }

// static int	count_argument(char **argv)
// {
// 	int	i;

// 	i = 0;
// 	while (argv[i])
// 		i++;
// 	return (i);
// }

int	ft_exit()
{
	return 0;
}
