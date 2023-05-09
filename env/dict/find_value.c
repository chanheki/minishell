#include "../../include/minishell.h"

char	*find_value(char *key)
{
	t_env_dict	*temp;

	temp = g_var.env_dict;
	while (temp)
	{
		if (!ft_strcmp(temp->key, key))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}
