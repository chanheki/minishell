
#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

/* cmd list */
typedef struct s_cmd_list
{
	char				*cmd;
	char				*option;
	struct s_cmd_list	*next_list;
}	t_cmd_list;

/* pipe fd */
typedef enum e_pipefd
{
	FD_READ = 0,
	FD_WRITE = 1
}	t_pipefd;

// excute.c
void		execute(t_ASTnode *cmdTree);
t_error		execute_parent(t_ASTnode *node);

// argv.c
char		**make_argv(t_ASTnode *node);
t_error		make_cmd_path(char *cmd_name, char **path, char **envp);
t_ASTnode	**make_cmd_list(t_ASTnode *root);

// redirect.c
t_error		redirect(t_ASTnode *node);

// heredoc.c
t_error		heredoc(t_ASTnode **cmd_list);
t_error		execute_heredoc(t_ASTnode *node);
void		set_tmp(void);

// terminal.c
void		set_terminal_attribute(void);
void		set_termianl(void);

// excute_child.c
t_error		execute_child(t_ASTnode *root);
t_error		create_childs_processes(t_ASTnode **cmd_list, pid_t *pid_list);

#endif