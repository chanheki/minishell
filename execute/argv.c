#include "../include/minishell.h"

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

char	**make_argv(t_ASTnode *node)
{
	t_token	*token;	
	char	**argv;
	int		i;

	argv = (char **)ft_calloc(count_argument(node) + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	while (node)
	{
		token = node->token;
		argv[i] = ft_strdup(token->value);
		if (!(argv[i]))
		{
			ft_split_free(argv);
			return (NULL);
		}
		node = node->left;
		i++;
	}
	return (argv);
}
