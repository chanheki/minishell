
#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

// builtin.c
int	check_builtin(char *cmd);
int	exec_builtin(t_cmd_list *cmd_list);

// builtin dir
void	ft_cd(char *option);
void	ft_echo(char *option);
void	ft_env();
void	ft_exit();
void	ft_export();
void	ft_pwd();
void	ft_unset();

#endif