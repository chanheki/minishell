#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\033[0;32;3mJIP-Shell$\033[0m "

# include "../lib/libft.h"
# include <signal.h>
# include <stdio.h>
# include <term.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <readline/history.h>
# include "readline/readline.h"

/* custom includes */
# include "error.h"
# include "parse.h"
# include "utill.h"
# include "prompt.h"
# include "signal.h"
# include "execute.h"
# include "builtin.h"

typedef struct s_global
{
	int				argc;
	char			**argv;
	char			**envp;
	int				exit_status;
	struct termios	old_term;
	struct termios	new_term;
	int				is_signal;
	char			*tmp_path;
}	t_global;

extern t_global	g_var;

#endif
