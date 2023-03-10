#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\033[0;32;3mJIP-Shell$\033[0m "

# include "../lib/libft.h"
# include <signal.h>
# include <stdio.h>
# include <term.h>
# include <sys/ioctl.h>
# include <readline/history.h>
# include "readline/readline.h"

/* custom includes */
# include "execute.h"
# include "utill.h"
# include "prompt.h"
# include "signal.h"

enum	e_token_type {
	NORMAL = -1,
	PIPE = '|',
	AMPERSAND = '&',
	QUOTE = '\'',
	DQUOTE = '\"',
	SEMICOLON = ';',
	ESCAPE_SEQUENCE = '\\',
	// TAB = '\t',
	NEW_LINE = '\n',
	REDIRECT_IN = '>',
	REDIRECT_OUT = '<'
	// DREDIRECT_IN = '<<',
	// DREDIRECT_OUT = '>>',
};

typedef struct s_ASTnode
{
	int					type;
	char				*value;
	struct s_ASTnode	*left;
	struct s_ASTnode	*right;
}	t_ASTnode;

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

typedef enum e_error
{
	ERROR	=	-2,
	FAIL	=	-1,
	SUCCESS	=	0
}	t_error;

typedef struct s_global
{
	int		argc;
	char	**argv;
	char	**envp;
	int		exit_status;
}	t_global;

extern t_global	g_var;

void	set_signal(void);

#endif
