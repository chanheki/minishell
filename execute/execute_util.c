/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 02:07:59 by chanheki          #+#    #+#             */
/*   Updated: 2023/05/11 03:01:20 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Description: pid list를 만든다.(cmd)
 *            : 들어오는 cmd list의 갯수만큼 보관할 pid list를 만든다.
 * Param.   #1: **cmd_list
 * Return     : **pidlist (해당 cmd의 pid값들을 저장 할 공간)
 */
pid_t	*empty_pid_storage(t_ASTnode **cmd_list)
{
	pid_t	*pid_list;
	int		i;

	i = 0;
	while (cmd_list[i])
		i++;
	pid_list = (pid_t *)ft_calloc(i + 1, sizeof(pid_t));
	return (pid_list);
}

/*
 * Description: wait process (*pidlist)
 *            : pid list에 담긴 특정 pid들을 기다린다.
 *            : 자식 프로세스들이 끝날 때까지 기다린다.
 *            : 
 * Param.   #1: **pid_list
 * Return     : status
 */
int	wait_process(pid_t *pid_list)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (pid_list[i])
	{
		waitpid(pid_list[i], &status, 0);
		if (0 < status && status < 256)
			status = (128 + status) << 8;
		i++;
	}
	return (status >> 8);
}

/*
 * Description: last_process(cmd)
 *            : pipe, fork후 자식 마지막 process에서 실행
 *            : 자식프로세스 = dup2로 입력과 출력을 지정한 뒤 실행한다.
 *            : 부모프로세스 = 재사용 방지를 위해 파이프를 닫아준다.
 * Param.   #1: node (root)
 * Param.   #1: node (root)
 * Return     : SUCCESS : 성공
 *            : ERROR: 실패
 */
pid_t	last_process(t_ASTnode *cmd_node, int before_fd)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
	{
		if ((before_fd != STDIN_FILENO
				&& ft_dup2(before_fd, STDIN_FILENO) == ERROR)
			|| execute_child_process(cmd_node) == ERROR)
			exit(EXIT_GENERAL_ERROR);
	}
	if (before_fd != STDIN_FILENO && close(before_fd) == -1)
		return (0);
	return (child_pid);
}
