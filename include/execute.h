/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:23:19 by chanheki          #+#    #+#             */
/*   Updated: 2023/05/11 02:10:08 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
t_error		execute_child_process(t_ASTnode *cmd_node);

// argv.c
char		**generate_argv(t_ASTnode *node);
t_error		generate_cmd_path(char *cmd_name, char **path, char **envp);
t_ASTnode	**generate_cmd_list(t_ASTnode *root);

// redirect.c
t_error		redirect(t_ASTnode *node);

// heredoc.c
t_error		heredoc(t_ASTnode **cmd_list);
t_error		execute_heredoc(t_ASTnode *node);
void		set_tmp(void);

// excute_child.c
t_error		execute_child(t_ASTnode *root);
t_error		create_childs_processes(t_ASTnode **cmd_list, pid_t *pid_list);

// excute_util.c
pid_t		*empty_pid_storage(t_ASTnode **cmd_list);
int			wait_process(pid_t *pid_list);
pid_t		last_process(t_ASTnode *cmd_node, int before_fd);

// builtin.c
bool		is_builtin_cmd(t_ASTnode *node);

#endif