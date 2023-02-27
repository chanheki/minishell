#ifndef MINISHELL_H
# define MINISHELL_H

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
	REDIRECT_OUT = '<',
	DREDIRECT_IN = '<<',
	DREDIRECT_OUT = '>>',
};

typedef struct s_ASTnode
{
	int					type;
	char				*value;
	struct s_ASTnode	*left;
	struct s_ASTnode	*right;
}	t_ASTnode;

#endif
