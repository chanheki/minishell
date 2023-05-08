
#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

// builtin.c
int		check_builtin(char *cmd);
int		exec_builtin(char *path, char **argv);
t_error	execute_parent(t_ASTnode *node);

// builtin dir
int	ft_cd(char **option);
int	ft_echo(char **option);
int	ft_env();
int	ft_exit();
int	ft_export();
int	ft_pwd();

/*---------------------------------- UNSET ----------------------------------*/
int	check_unset_argv(char *argv);
int	ft_unset(char **argv);

#endif