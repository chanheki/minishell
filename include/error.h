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
	EXIT_BUILT_IN_FAIL = 2,
	EXIT_COMMAND_NOT_EXEC = 126,
	EXIT_COMMAND_NOT_FOUND = 127,
	EXIT_PASSING_INVALID = 128,
	EXIT_BY_SIGNAL = 128,
	EXIT_OUT_OF_RANGE = 255
}	t_exitcode;

typedef enum e_error
{
	ERROR	=	-2,
	FAIL	=	-1,
	SUCCESS	=	0,
}	t_error;

#endif