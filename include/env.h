/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 21:22:14 by yena              #+#    #+#             */
/*   Updated: 2023/05/15 14:41:39 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_env_dict
{
	char				*key;
	char				*value;
	struct s_env_dict	*next;
	struct s_env_dict	*prev;
}	t_env_dict;

/*----------------------------------- ENV -----------------------------------*/
int		initialize_env(char **env);
void	initialize_env_dict(t_env_dict **dict, char *key, char *value);
int		set_env(char *key, char *value);
char	*create_env_string(char *key, char *value);
int		change_env_value(char *key, char *value);
void	update_envp(void);

/*----------------------------------- DICT ----------------------------------*/
void	add_to_env_dict(t_env_dict **dict, t_env_dict *new_dict);
void	free_one_env_dict(t_env_dict *dict);
void	free_env_dict(t_env_dict *dict);
bool	is_already_in(char *key);
char	*find_value(char *key);
void	delete_env(char *key);

/*----------------------------------- CAST ----------------------------------*/
int		cast_env_to_strings(char **env);
int		cast_env_to_dict(char **env);
char	*get_env_key(char *env);
char	*get_env_value(char *env);

#endif