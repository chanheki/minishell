
#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

// builtin.c
bool	is_builtin_command(t_ASTnode *node);
int		exec_builtin(char *path, char **argv);

// builtin dir
int	ft_cd(char **option);
int	ft_echo(char **option);
int	ft_env();
int	ft_exit();
int	ft_export();
int	ft_pwd(void);

/*---------------------------------- UNSET ----------------------------------*/
int	check_unset_argv(char *argv);
int	ft_unset(char **argv);

#endif