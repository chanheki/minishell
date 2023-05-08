#include "../include/minishell.h"

/*
 * Description: cmd의 argument(option)의 count를 센다.
 *            : 해당 cmd의 좌측으로 달린 모든 노드의 갯수를 반환한다.
 * Param.   #1: cmd
 * Return     : int count
 */
static int	count_argument(t_ASTnode *node)
{
	int	count;

	count = 0;
	while (node)
	{
		count++;
		node = node->left;
	}
	return (count);
}

/*
 * Description: argv를 만든다.(cmd)
 *            : 해당 cmd의 좌측으로 달린 모든 노드를 문자열 배열로 생성한다.
 * Param.   #1: cmd
 * Return     : **argv (해당 cmd의 옵션값들)
 */
char	**generate_argv(t_ASTnode *cmd)
{
	char	**argv;
	int		i;

	argv = (char **)ft_calloc(count_argument(cmd) + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	while (cmd)
	{
		argv[i] = ft_strdup(cmd->token->value);
		if (!(argv[i]))
		{
			ft_split_free(argv);
			return (NULL);
		}
		cmd = cmd->left;
		i++;
	}
	return (argv);
}
