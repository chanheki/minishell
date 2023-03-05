#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\033[0;32;3mJIP-Shell$\033[0m "

# include "../lib/libft.h"
# include "readline/readline.h"
# include <readline/history.h>
# include <term.h>
# include <stdio.h>
# include <sys/ioctl.h>

/* custom includes */
# include "execute.h"
# include "utill.h"

enum	e_token_type {
	NORMAL = -1,
	PIPE = '|',
	AMPERSAND = '&',
	QUOTE = '\'',
	DQUOTE = '\"',
	SEMICOLON = ';',
	ESCAPE_SEQUENCE = '\\',
	TAB = '\t',
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

typedef struct s_global
{
	char			**envp;
}	t_global;

extern t_global	g_var;

#endif
