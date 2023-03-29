
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

#endif