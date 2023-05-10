/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 05:10:32 by chanheki          #+#    #+#             */
/*   Updated: 2023/05/11 05:16:29 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Description: sigint heredoc 대체 함수의 구현
 *            : heredoc 상황에서의 sigint 구현
 *            : ctrl+c의 입력이 들어오면 해당 함수가 실행된다.
 */
void	sigint_heredoc(int signumber)
{
	if (signumber == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_var.is_signal = 1;
		g_var.exit_status = 1;
	}
}

/*
 * Description: sigint prompt 대체 함수의 구현
 *            : ctrl+c의 입력이 들어오면 해당 함수가 실행된다.
 */
void	sigint_prompt(int signumber)
{
	if (signumber == SIGINT)
	{
		g_var.exit_status = 1;
		rl_replace_line("", 1);
		ft_putendl_fd("", STDOUT_FILENO);
		if (rl_on_new_line() == FAIL)
			exit(EXIT_FAILURE);
		rl_redisplay();
	}
}

/*
 * Description: 시그널을 세팅한다.
 *            : 시그널 핸들러(signal handler) ctrl+c 를 비활성화하고, 해당 시그널을 구현한다.
 *            : ctrl+\를 ignore한다.
 *            : 둘 중 하나라도 실패하면 전역변수 exit_status에 에러값을 전달하고 t_error을 반환한다.
 * Return     : SUCCESS : 성공
 *            : ERROR: 실패
 */
t_error	set_signal(void)
{
	rl_catch_signals = 0;
	if (signal(SIGINT, sigint_prompt) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		g_var.exit_status = -1;
		return (ERROR);
	}
	return (SUCCESS);
}
