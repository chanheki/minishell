#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct	s_env_dict
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env_dict;

typedef struct	s_env
{
	t_env_dict		*dict;
	char			**env_str;
}	t_env;

/*----------------------------------- ENV -----------------------------------*/
int	initialize_env(char **env);

#endif
