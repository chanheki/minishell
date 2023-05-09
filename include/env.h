#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct	s_env_dict
{
	char				*key;
	char				*value;
	struct s_env_dict	*next;
	struct s_env_dict	*prev;
}	t_env_dict;

/*----------------------------------- ENV -----------------------------------*/
int		initialize_env(char **env);
void	initialize_env_dict(t_env_dict **dict, char *key, char *value);

/*----------------------------------- DICT ----------------------------------*/
void	add_to_env_dict(t_env_dict **dict, t_env_dict *new_dict);
void	free_env_dict(t_env_dict *dict);
char	*find_value(char *key);

/*----------------------------------- CAST ----------------------------------*/
int		cast_env_to_dict(char **env);
char	*get_env_key(char *env);
char	*get_env_value(char *env);

#endif