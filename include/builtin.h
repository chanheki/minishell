
#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

// builtin.c
int		check_builtin(char *cmd);
int		exec_builtin(char *path, char **argv);

// builtin dir
int	ft_cd(char **option);
int	ft_echo(char **option);
int	ft_env();
int	ft_exit();
int	ft_export();
int	ft_pwd();
int	ft_unset();

#endif