/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 03:02:34 by chanheki          #+#    #+#             */
/*   Updated: 2023/05/11 03:02:34 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Description: 터미널을 세팅한다.
 *            : STDIN_FILENO
 *            : g_var.new_term에 입력된 값으로 세팅한다.
 *            : TCSANOW: 즉시 적용합니다.
 *            : TCSADRAIN: fildes의 출력이 비워질때 까지 대기한 후 속성값을 적용.
 *            : TCSAFLUSH: fildes의 출력이 비워질때 까지 대기한 후,
 *            : 입력 큐에서 남아 있는 문자들을 모두 삭제한 후 속성값을 적용합니다.
 */
void	set_terminal_attribute(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_var.new_term));
}

/*
 * Description: 터미널 초기 세팅을 가져온다.
 *            : old_term = term 초기 세팅
 *            : new_term = minishell 에서 사용 할 terminal 세팅
 */
void	get_termianl(void)
{
	tcgetattr(STDIN_FILENO, &(g_var.old_term));
	tcgetattr(STDIN_FILENO, &(g_var.new_term));
}

/*
 * Description: 터미널 세팅 초기화 진행.
 *            : 제어문자 출력하지 않게 설정.
 *            : 터미널 자체의 세팅이다. 프로세스들도 영향을 받는다.
 */
void	set_termianl(void)
{
	get_termianl();
	g_var.new_term.c_lflag &= ~ECHOCTL;
	g_var.new_term.c_cc[VQUIT] = 0;
	set_terminal_attribute();
}
