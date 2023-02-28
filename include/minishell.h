#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"

enum	e_token_type {
	NORMAL = -1,
	PIPE = '|',
	DPIPE = "||",
	AMPERSAND = '&',
	DAMPERSAND = "&&",
	QUOTE = '\'',
	DQUOTE = '\"',
	SEMICOLON = ';',
	ESCAPE_SEQUENCE = '\\',
	TAB = '\t',
	NEW_LINE = '\n',
	REDIRECT_IN = '>',
	REDIRECT_OUT = '<',
	DREDIRECT_IN = '<<',
	DREDIRECT_OUT = '>>',
	WILDCARD = '*',
	PARENTHESIS_OPEN = '(',
	PARENTHESIS_CLOSE = ')',
};

enum	e_node_type {
	PIPE_NODE,
	DPIPE_NODE,
	BACKGROUND_NODE,
	SEQUENCE_NODE,
	REDIRECT_IN_NODE,
	REDIRECT_OUT_NODE,
	CMD_PATH_NODE,
	ARGUMENT_NODE,
};

typedef struct s_ASTnode
{
	int					type;
	char				*value;
	struct s_ASTnode	*parent;
	struct s_ASTnode	*left;
	struct s_ASTnode	*right;
}	t_ASTnode;

#endif
