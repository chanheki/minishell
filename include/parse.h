#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>

enum	e_token_type {
	NORMAL,
	PIPE = '|',
	DPIPE,
	QUOTE = '\'',
	DQUOTE = '\"',
	REDIRECT_IN = '<',
	DREDIRECT_IN,
	REDIRECT_OUT = '>',
	DREDIRECT_OUT,
	SEMICOLON = ';',
	AMPERSAND = '&',
	DAMPERSAND,
	WILDCARD = '*',
	PARENTHESIS_OPEN = '(',
	PARENTHESIS_CLOSE = ')',
	EXPANSION = '$',
	SPACE = ' ',
	ESCAPE = '\\',
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

enum	e_node_direction {
	LEFT,
	RIGHT,
	PARENT,
};

enum	e_token_status {
	IN_NORMAL,
	IN_QUOTE,
	IN_DQUOTE,
	IN_PARENTHESIS,
	IN_ESCAPE,
	IN_EXPANSION,
};

typedef struct s_token {
	char				*value;
	enum e_token_type	type;
	bool				is_in_quote;
	bool				is_in_dquote;
	bool				is_in_escape;
	struct s_token		*next;

}	t_token;

typedef struct s_ASTnode
{
	int					type;
	void				*value;
	struct s_ASTnode	*parent;
	struct s_ASTnode	*left;
	struct s_ASTnode	*right;
}	t_ASTnode;

typedef struct	s_cursor
{
	void	*current;
	void	*previous;
	void	*next;
}	t_cursor;

/*---------------------------------- PARSE ----------------------------------*/
char				**preprocess_line(char *line);
t_token				*parse_command_line(char *line);
bool				is_valid_syntax(t_token *token);

/*--------------------------------- AST_TREE --------------------------------*/
void				add_node_to_direction(t_ASTnode **node, t_ASTnode *new,
						int direction);
void				clear_nodes(t_ASTnode **root);
t_ASTnode			*create_new_node(void *value, int type);
t_ASTnode			*set_ast_node(char *trimmed_line);

/*---------------------------------- TOKEN ----------------------------------*/
void				add_token_to_tail(t_token **token, t_token *new);
t_token				*create_new_token(void *value, enum e_token_type type);
t_token				*get_tail_token(t_token **token);
void				join_token_value(t_token **token,
						char *trimmed_line, int *i);
void				set_normal_token(t_token **token,
						char *trimmed_line, int *i);
void				set_quote_token(t_token **token,
						char *trimmed_line, int *i);
enum e_token_type	get_operator_token_type(char c);
enum e_token_type	get_double_operator_token_type(char c);
void				set_operator_token(t_token **token,
						char *trimmed_line, int *i);
void				set_fd_redirection_token(t_token **token,
						char *trimmed_line, int *i);
void				set_token(t_token *token, char *trimmed_line, int *i);
void				free_token_list(t_token **token);
t_token				*tokenize_line(char *trimmed_line);

/*------------------------------ COMMAND_SPLIT -------------------------------*/
size_t				get_split_command_count(char *arguments);
char				**split_command_line(char *argument_str);

#endif
