
#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

typedef struct s_cmd_list
{
	char				*cmd;
	char				*option;
	struct s_cmd_list	*next_list;
}	t_cmd_list;

// excute.c
void	execute(t_ASTnode *cmdTree);
t_error	execute_parent(t_ASTnode *node);

// argv.c
char	**make_argv(t_ASTnode *node);

t_error		make_cmd_path(char *cmd_name, char **path, char **envp);
t_ASTnode	**make_cmd_list(t_ASTnode *root);


// redirect.c

t_error	redirect(t_ASTnode *node);


// heredoc.c

t_error	execute_all_heredoc(t_ASTnode **cmd_list);

// terminal.c

void	set_terminal_attribute(void);
void	get_terminal_setting(void);

// excute_child.c

t_error		execute_child(t_ASTnode *root);
t_error		create_childs(t_ASTnode **cmd_list, pid_t *pid_list);

#endif