#ifndef PROMPT_H
# define PROMPT_H

# include "minishell.h"

void	initialize_setting();
void	initialize_global_variable(int argc, char **argv, char **env);
void	validator();
void	check_eof(char *str);

#endif