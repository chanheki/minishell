#include "../../include/minishell.h"

void	delete_env(char *key)
{
	t_env_dict	*temp;
	t_env_dict	*next;

	if (!g_var.env_dict)
		return ;
	temp = g_var.env_dict;
	while (temp)
	{
		next = temp->next;
		if (!ft_strcmp(temp->key, key))
		{
			if (!temp->prev)
				g_var.env_dict = next;
			free_one_env_dict(temp);
		}
		temp = next;
	}
	update_envp();
}
