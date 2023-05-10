/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:22:59 by chanheki          #+#    #+#             */
/*   Updated: 2023/05/11 01:28:37 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/*
 * <exit code>
 * 0       => Success
 * 1       => General Error
 * 2       => Built-in Shell Command Error
 * 126     => Command is found but is not Executable
 * 127     => Command not found
 * 128     => not used on shell
 * 128 + N => exit by signal N
 * 255     => Out of Range
 */
typedef enum e_exitcode
{
	EXIT_GENERAL_ERROR = 1,
	EXIT_BUILT_IN_FAIL = 2,
	EXIT_COMMAND_NOT_EXEC = 126,
	EXIT_COMMAND_NOT_FOUND = 127,
	EXIT_PASSING_INVALID = 128,
	EXIT_BY_SIGNAL = 128,
	EXIT_OUT_OF_RANGE = 255
}	t_exitcode;

/*
 * <custom exit code>
 */
typedef enum e_custom_exitcode
{
	EXIT_NORMAL = 0,
	EXIT_TOO_MANY_ARGUMENTS = 1,
	EXIT_SIGNAL_ERROR = 1,
}	t_custom_exitcode;

typedef enum e_error
{
	ERROR	=	-2,
	FAIL	=	-1,
	SUCCESS	=	0,
}	t_error;

#endif