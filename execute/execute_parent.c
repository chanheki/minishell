/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 02:07:54 by chanheki          #+#    #+#             */
/*   Updated: 2023/05/11 02:07:54 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Description: set ready to excute (fd, cmdlist, cmdargv)
 *            : 실행하기 위한 준비를 한다.
 *            : 1. fd를 dup하여 저장한다.
 *            : 2. cmd list의 heredoc을 전부 처리한다.
 *            : 3. redirect를 전부 처리한다.
 * Param.   #1: node (cmd)
 * Return     : SUCCESS : 성공
 *            : ERROR: 실패
 */
static t_error	set_ready_to_excute(
	int fd[2], t_ASTnode **cmd_list, char **cmd_argv)
{
	fd[FD_READ] = dup(STDIN_FILENO);
	fd[FD_WRITE] = dup(STDOUT_FILENO);
	if (fd[FD_READ] < 0 || fd[FD_WRITE] < 0
		|| heredoc(cmd_list) != SUCCESS
		|| redirect(cmd_list[0]) == ERROR)
	{
		close(fd[FD_READ]);
		close(fd[FD_WRITE]);
		ft_split_free(cmd_argv);
		free(cmd_list);
		return (ERROR);
	}
	return (SUCCESS);
}

/*
 * Description: excute will termiante
 *            : excute가 끝나기 전에 실행된다.
 *            : 1. fd를 원상복구 시킨다.
 *            : 2. cmd list를 할당 해제한다.
 *            : 3. cmd argv를 할당 해제한다.
 * Param.   #1: node (cmd)
 * Return     : SUCCESS : 성공
 *            : ERROR: 실패
 */
static void	execute_will_terminate(
	int fd[2], t_ASTnode **cmd_list, char **cmd_argv)
{
	ft_dup2(fd[FD_READ], STDIN_FILENO);
	ft_dup2(fd[FD_WRITE], STDOUT_FILENO);
	free(cmd_list);
	ft_split_free(cmd_argv);
}

/*
 * Description: execute_parent(cmd)
 *            : 부모 process에서 실행. (builtin)
 *            : 해당 노드의 argv와 cmdlist를 만들어서 실행 준비를 하고
 *            : builtin 함수를 실행 시킨다.
 * Param.   #1: node (cmd)
 * Return     : SUCCESS : 성공
 *            : ERROR: 실패
 */
t_error	execute_parent(t_ASTnode *node)
{
	t_ASTnode	**cmd_list;
	char		**cmd_argv;
	char		*path;
	int			fd[2];

	path = node->token->value;
	cmd_argv = generate_argv(node);
	if (!cmd_argv)
		return (ERROR);
	cmd_list = generate_cmd_list(node);
	if (!cmd_list)
	{
		ft_split_free(cmd_argv);
		return (ERROR);
	}
	if (set_ready_to_excute(fd, cmd_list, cmd_argv) == ERROR)
		return (ERROR);
	g_var.exit_status = execute_builtin(path, cmd_argv, P_PARENT);
	execute_will_terminate(fd, cmd_list, cmd_argv);
	return (SUCCESS);
}
