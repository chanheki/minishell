/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:54:45 by yena              #+#    #+#             */
/*   Updated: 2023/05/11 04:57:05 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Description: 토큰의 문법 유효성을 검사한다.
 *              1. 괄호의 짝이 맞는지 검사한다.
 *              2. 괄호의 위치가 올바른지 검사한다.
 *              3. 리다이렉션의 위치가 올바른지 검사한다.
 *              4. 명령어의 위치가 올바른지 검사한다.
 * Param.   #1: 토큰 리스트의 첫 번째 토큰 주소
 * Return     : true : 유효한 문법
 *              false: 유효하지 않은 문법
 */
bool	is_valid_syntax(t_token *token)
{
	g_var.exit_status = 2;
	if (!is_pair_of_parenthesis(token))
		return (false);
	else if (!is_valid_parenthesis(token))
		return (false);
	else if (!is_valid_redirection(token))
		return (false);
	else if (!is_valid_command(token))
		return (false);
	else
	{
		g_var.exit_status = 0;
		return (true);
	}
}
