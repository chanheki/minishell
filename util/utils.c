
#include "../include/minishell.h"
#include <sys/stat.h>

/*
 * Description: ft_dup2 
 *            : fd2를 닫는다.
 *            : fd1 파일 디스크립터를 fd2로 dup2한다.(fd2가 fd1과 동일한 파일을 가리키게 한다.)
 *            : fd1을 닫는다.
 * Param.   #1: fd1
 *          #2: fd2
 * Return     : SUCCESS : 성공
 *            : EXIT_BUILT_IN_FAIL = 2 실패
 */
t_error	ft_dup2(int fd1, int fd2)
{
	if (close(fd2) == -1)
		return (ERROR);
	if (dup2(fd1, fd2) == -1)
		return (ERROR);
	if (close(fd1) == -1)
		return (ERROR);
	return (SUCCESS);
}

/*
 * Description: is dir ? 
 *            : path의 경로의 파일이 dir인지 확인한다.
 * Param.   #1: path
 * Return     : true = 참
 *            : false = 거짓
 */
bool	is_directory(char *path)
{
	struct stat	file_info;

	if (lstat(path, &file_info) < 0)
		return (false);
	if ((S_IFMT & file_info.st_mode) == S_IFDIR)
		return (true);
	return (false);
}

/*
 * Description: check token type operator
 *            : 해당 토큰이 operator type인지 체크한다.
 * Param.   #1: token
 * Return     : true : &&, || 타입이 맞음
 *            : false: 해당 타입이 아님.
 */
int	check_token_type_operator(t_token *token)
{
	if (token == NULL || token->value == NULL)
		return (false);
	if (token->type == DAMPERSAND || token->type == DPIPE)
		return (true);
	return (false);
}

int	check_token_type(t_token *token, t_token_type type)
{
	if (token == NULL || token->value == NULL)
		return (false);
	if (token->type == (t_token_type)(type))
		return (true);
	return (false);
}