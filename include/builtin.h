/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 05:03:04 by chanheki          #+#    #+#             */
/*   Updated: 2023/05/11 06:23:31 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

typedef enum e_process_type
{
	P_PARENT = 0,
	P_CHILD = 1
}	t_process_type;

// builtin.c
bool	is_builtin_command(t_ASTnode *node);
int		execute_builtin(char *path, char **argv, t_process_type type);

// builtin dir
int		ft_cd(char **option);
int		ft_echo(char **option);
int		ft_env(char **argv);
int		ft_exit(char **argv, t_process_type type);
int		ft_export(char **argv);
int		ft_pwd(void);

/*--------------------------------- EXPORT ----------------------------------*/
int		print_envp(void);

/*----------------------------------- CD ------------------------------------*/
int		move_to_dir(char *path);
int		update_cwd(void);
int		move_to_home(void);
int		ft_cd(char **path);

/*---------------------------------- UNSET ----------------------------------*/
int		ft_unset(char **argv);

#endif