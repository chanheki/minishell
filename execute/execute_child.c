/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 02:00:28 by chanheki          #+#    #+#             */
/*   Updated: 2023/05/11 11:01:56 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Description: child_execve
 *            : 자식 프로세스 실행을 해주는 부분
 *            : builtin command인지 확인한 후 builtin 커맨드의 경우는
 *            : exit로 묶어서 실행한다. (builtin이 아닌 경우 바로 실행.)
 * Param.   #1: *node 
 * Param.   #2: *path 
 * Param.   #3: **argv 
 */
static void	child_execve(t_ASTnode *node, char *path, char **argv)
{
	char	*builtin;

	builtin = node->token->value;
	if (is_builtin_command(node) == false && !path)
	{
		ft_putstr_fd("JIP-shell: ", STDERR_FILENO);
		ft_putstr_fd(argv[0], STDERR_FILENO);
		if (ft_strcmp(argv[0], "") != 0 && is_directory(argv[0]))
		{
			ft_putendl_fd(": is a directory", STDERR_FILENO);
			exit(EXIT_COMMAND_NOT_EXEC);
		}
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit(EXIT_COMMAND_NOT_FOUND);
	}
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR
		|| signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(EXIT_SIGNAL_ERROR);
	jipshell_will_terminate();
	if (is_builtin_command(node) == true)
		exit(execute_builtin(builtin, argv, P_CHILD));
	execve(path, argv, g_var.envp);
	exit(EXIT_NORMAL);
}

/*
 * Description: execute_child_process(cmd node)
 *            : 자식 프로세스 실행을 위한 단계.
 *            : cmdlist와 pidlist를 만들어서 준비하고
 *            : child process를 만든 후 실행한 뒤 process를 기다린다.
 * Param.   #1: node (root)
 * Return     : SUCCESS : 성공
 *            : ERROR: 실패
 */
t_error	execute_child_process(t_ASTnode *cmd_node)
{
	char	*path;
	char	**cmd_argv;

	cmd_argv = generate_argv(cmd_node);
	if (!cmd_argv)
		return (ERROR);
	if (redirect(cmd_node) == ERROR
		|| generate_cmd_path(cmd_argv[0], &path, g_var.envp) == ERROR)
	{
		ft_split_free(cmd_argv);
		return (ERROR);
	}
	child_execve(cmd_node, path, cmd_argv);
	return (SUCCESS);
}

/*
 * Description: execute_child(cmd)
 *            : pipe, fork후 자식 process에서 실행.
 *            : 자식프로세스 = dup2로 입력과 출력을 지정한 뒤 실행한다.
 *            : 부모프로세스 = 재사용 방지를 위해 파이프를 닫아준다.
 * Param.   #1: cmd_node 
 * Param.   #2: before_fd 
 * Return     : SUCCESS : 성공
 *            : ERROR: 실패
 */
static pid_t	fork_child(t_ASTnode *cmd_node, int *before_fd)
{
	pid_t	child_pid;
	int		fd[2];
	int		temp_fd;

	if (pipe(fd) == -1)
		return (0);
	temp_fd = *before_fd;
	*before_fd = fd[FD_READ];
	child_pid = fork();
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
	{
		if (close(fd[FD_READ]) < 0
			|| (temp_fd != STDIN_FILENO
				&& ft_dup2(temp_fd, STDIN_FILENO) == ERROR)
			|| ft_dup2(fd[FD_WRITE], STDOUT_FILENO) == ERROR
			|| execute_child_process(cmd_node) == ERROR)
			exit(EXIT_GENERAL_ERROR);
	}
	if ((temp_fd != STDIN_FILENO && close(temp_fd) == -1)
		|| close(fd[FD_WRITE]) == -1)
		return (0);
	return (child_pid);
}

/*
 * Description: execute_child(cmd)
 *            : 자식 process에서 실행.
 *            : cmdlist와 pidlist를 만들어서 준비하고
 *            : child process를 만든 후 실행한 뒤 process를 기다린다.
 * Param.   #1: **cmd_list 
 * Param.   #2: **pid_list 
 * Return     : SUCCESS : 성공
 *            : ERROR: 실패
 */
t_error	create_childs_processes(t_ASTnode **cmd_list, pid_t *pid_list)
{
	int	i;
	int	before_fd;

	before_fd = STDIN_FILENO;
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		return (ERROR);
	i = 0;
	while (cmd_list[i + 1])
	{
		pid_list[i] = fork_child(cmd_list[i], &before_fd);
		if (pid_list[i] == 0)
			return (ERROR);
		i++;
	}
	pid_list[i] = last_process(cmd_list[i], before_fd);
	if (pid_list[i] == 0)
		return (ERROR);
	return (SUCCESS);
}

/*
 * Description: execute_child(cmd)
 *            : 자식 process에서 실행.
 *            : cmdlist와 pidlist를 만들어서 준비하고
 *            : child process를 만든 후 실행한 뒤 process를 기다린다.
 * Param.   #1: node (root)
 * Return     : SUCCESS : 성공
 *            : ERROR: 실패
 */
t_error	execute_child(t_ASTnode *root)
{
	t_ASTnode	**cmd_list;
	pid_t		*pid_list;

	cmd_list = generate_cmd_list(root);
	if (!cmd_list)
		return (ERROR);
	pid_list = empty_pid_storage(cmd_list);
	if (!pid_list
		|| heredoc(cmd_list) != SUCCESS
		|| create_childs_processes(cmd_list, pid_list) == ERROR)
	{
		free(pid_list);
		free(cmd_list);
		return (ERROR);
	}
	g_var.exit_status = wait_process(pid_list);
	free(pid_list);
	free(cmd_list);
	return (SUCCESS);
}
