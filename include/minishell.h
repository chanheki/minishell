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
# include "env.h"

/*
 * <exit code>
 * 0       => Success
 * 1       => General Error
 * 2       => Built-in Shell Command Error
 * 126     => Command is found but is not Executable
 * 127     => Command not found
 * 128     => not used on shell
 * 128 + N => exit by signal N
 * 255     => Out of Range
 */
typedef enum e_exitcode
{
	EXIT_BUILT_IN_FAIL = 2,
	EXIT_COMMAND_NOT_EXEC = 126,
	EXIT_COMMAND_NOT_FOUND = 127,
	EXIT_PASSING_INVALID = 128,
	EXIT_BY_SIGNAL = 128,
	EXIT_OUT_OF_RANGE = 255
}	t_exitcode;

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
