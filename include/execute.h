
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

// argv.c

char	**make_argv(t_ASTnode *node);


t_error	create_childs(t_ASTnode **cmd_list, pid_t *pid_list);
t_error	apply_redirections(t_ASTnode *node);
t_error	make_cmd_path(char *cmd_name, char **path, char **envp);
t_ASTnode	**make_cmd_list(t_ASTnode *root);
#endif