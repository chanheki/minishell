
#ifndef SIGNAL_H
# define SIGNAL_H

# include "minishell.h"


void	set_signal(void);
void	sigint_prompt(int signumber);
void	sigint_heredoc(int signumber);

#endif