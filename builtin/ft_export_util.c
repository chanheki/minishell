
#include "../include/minishell.h"

static void	sort_arr(char **arr_key, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (ft_strcmp(arr_key[j], arr_key[j + 1]) > 0)
			{
				tmp = arr_key[j];
				arr_key[j] = arr_key[j + 1];
				arr_key[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	envp_length()
{
	int			i;
	t_env_dict	*dic;

	i = 0;
	dic = g_var.env_dict;
	while (dic)
	{
		i++;
		dic = dic->next;
	}
	return (i);
}

static void	print_envp_line(char *key)
{
	char	*value;

	value = find_value(key);
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(key, STDOUT_FILENO);
	if (value)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static char	**generate_envp_arr()
{
	char		**arr_key;
	t_env_dict	*dic;
	int			len;
	int			i;

	len = envp_length();
	arr_key = (char **)calloc(sizeof(char *), (len + 1));
	if (!arr_key)
		return (NULL);
	i=0;
	dic = g_var.env_dict;
	while (dic)
	{
		arr_key[i] = dic->key;
		i++;
		dic = dic->next;
	}
	sort_arr(arr_key, len);
	return (arr_key);
}

int	print_envp()
{
	int		i;
	char	**arr_key;

	arr_key = generate_envp_arr();
	if (!arr_key)
		return (1);
	i = 0;
	while (arr_key[i])
	{
		print_envp_line(arr_key[i]);
		i++;
	}
	free(arr_key);
	return (0);
}
