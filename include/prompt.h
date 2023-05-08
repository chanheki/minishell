#ifndef PROMPT_H
# define PROMPT_H

# include "minishell.h"

void	initialize_setting(void);
void	initialize_global_variable(int argc, char **argv, char **env);
void	validator(void);
void	check_signal_eof(char *str);

#endif