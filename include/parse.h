/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:52:52 by yena              #+#    #+#             */
/*   Updated: 2023/05/11 06:54:30 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../lib/libft.h"
# include "minishell.h"
# include <stdbool.h>
# include <stdio.h>
# include <dirent.h>
# include <errno.h>

typedef enum e_token_type {
	NORMAL = 1,
	REDIRECT_IN = '<',
	DREDIRECT_IN,
	REDIRECT_OUT = '>',
	DREDIRECT_OUT,
	PARENTHESIS_OPEN = '(',
	PARENTHESIS_CLOSE = ')',
	AMPERSAND = '&',
	DAMPERSAND,
	PIPE = '|',
	DPIPE,
	QUOTE = '\'',
	DQUOTE = '\"',
	WILDCARD = '*',
	EXPANSION = '$',
	BLANK = ' ',
	ESCAPE = '\\',
}	t_token_type;

enum	e_node_direction {
	LEFT,
	RIGHT,
	ROOT,
	PARENT,
};

typedef struct s_token {
	char				*value;
	enum e_token_type	type;
	bool				is_in_quote;
	bool				is_in_dquote;
	bool				is_in_escape;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef struct s_ASTnode {
	t_token				*token;
	struct s_ASTnode	*parent;
	struct s_ASTnode	*left;
	struct s_ASTnode	*right;
}	t_ASTnode;

typedef struct s_cursor {
	void	*current;
	void	*previous;
	void	*next;
}	t_cursor;

/*---------------------------------- ERROR ----------------------------------*/
void				print_syntax_error(t_token *token);
void				print_command_not_found(t_token *token);

/*---------------------------------- PARSE ----------------------------------*/
char				**preprocess_line(char *line);
t_ASTnode			*parse_command_line(char *line);
bool				is_valid_syntax(t_token *token);
bool				is_valid_redirection(t_token *token);
bool				is_pair_of_parenthesis(t_token *token);
t_token				*get_last_token_in_parenthesis(t_token **token);
t_token				*get_tokens_in_parenthesis(t_token *open, t_token *close);
bool				is_correct_in_parenthesis(t_token *open, t_token *close);
bool				is_valid_parenthesis(t_token *token);
bool				is_valid_command(t_token *token);
t_ASTnode			*make_ast_tree(t_token **token);

/*--------------------------------- AST_TREE --------------------------------*/
void				add_node_to_direction(t_ASTnode **node, t_ASTnode *new_node,
						int direction);
void				clear_nodes(t_ASTnode **root);
t_ASTnode			*create_new_node(t_token *token);
t_ASTnode			*set_ast_node(char *trimmed_line);
t_ASTnode			*get_parent_node(t_ASTnode *node, t_token *current);
t_ASTnode			*get_root_node(t_ASTnode *ast_tree);
int					make_parenthesis_node(t_ASTnode **ast_tree,
						t_token **current);
int					make_operator_node(t_ASTnode **ast_tree, t_token *current);
int					make_command_node(t_ASTnode **ast_tree, t_token **current);
int					make_redirection_node(t_ASTnode **ast_tree,
						t_token **current);
int					make_normal_node(t_ASTnode **ast_tree, t_token **current);

/*---------------------------------- TOKEN ----------------------------------*/
void				add_token_to_tail(t_token **token, t_token *new);
t_token				*create_new_token(void *value, enum e_token_type type);
t_token				*get_tail_token(t_token **token);
t_token				*get_head_token(t_token *token);
char				*get_join_source(char c);
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
void				set_token(t_token **token, char *trimmed_line, int *i);
void				free_token(t_token **token);
void				free_token_list(t_token **token);
t_token				*tokenize_line(char *trimmed_line);
bool				is_operator(t_token *token);
bool				is_redirection(t_token *token);
bool				is_quote(char c);
void				interpret_expansion(t_token **token, char *trimmed_line,
						int *i);
void				postprocess_expansion(t_token **token);
char				*get_interpreted_env(char *trimmed_line,
						int start, int length);
void				interpret_env(t_token **token, char *trimmed_line, int *i);
void				interpret_exit_status(t_token **token, int *i);
void				delete_outer_quotes(t_token **token);
void				check_delete_quote(char *value, char *delete_flag);
void				rebuild_quote_string(t_token **temp_token,
						char *delete_flag);
void				interrupt_to_left(t_ASTnode **node, t_ASTnode *new_node);
bool				is_valid_wildcard(char *wildcard_value, \
								char *dir_name, size_t idx_w, size_t idx_d);
int					rebuild_wildcard(t_ASTnode **node, int *dir_count,
						char *dir_name);
int					interpret_wildcard(char *wildcard_value, t_ASTnode **node);
int					handle_wildcard(t_ASTnode *ast_tree);

#endif
