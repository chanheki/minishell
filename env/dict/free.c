#include "../../include/minishell.h"

void	free_env_dict(t_env_dict *dict)
{
	t_env_dict	*tmp;

	while (dict)
	{
		tmp = dict->next;
		free(dict->key);
		dict->key = NULL;
		free(dict->value);
		dict->value = NULL;
		free(dict);
		dict = tmp;
	}
}