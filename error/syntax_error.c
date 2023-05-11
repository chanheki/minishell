/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:52:43 by yena              #+#    #+#             */
/*   Updated: 2023/05/11 11:11:44 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
* Description: 토큰의 syntax error를 출력한다.
* Param.   #1: 에러가 발생한 토큰의 주소
* Return     : 없음
*/
void	print_syntax_error(t_token *token)
{
	ft_putstr_fd("JIP-shell: syntax error near unexpected token '", 2);
	ft_putstr_fd(token->value, 2);
	ft_putendl_fd("'", 2);
}

/*
* Description: 토큰의 command not found를 출력한다.
* Param.   #1: 에러가 발생한 토큰의 주소
* Return     : 없음
*/
void	print_command_not_found(t_token *token)
{
	ft_putstr_fd("JIP-shell: command not found: ", 2);
	ft_putendl_fd(token->value, 2);
}
