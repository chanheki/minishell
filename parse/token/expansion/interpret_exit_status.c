#include "../../../include/minishell.h"

/*
 * Description: 이전 foreground에서 실행된 명령어의 exit status를 토큰의 value에 저장한다.
 * Param.   #1: 토큰의 주소
 * Param.   #2: 해석할 환경변수가 포함된 커맨드 라인
 * Param.   #3: 커맨드 라인 내 환경변수의 시작 인덱스. '?'의 위치를 가리키고 있음
 * Return     : 없음
 */
void	interpret_exit_status(t_token **token, int *i)
{
	char	*exit_status;
	char	*temp;

	exit_status = ft_itoa(g_var.exit_status);
	if (!(*token)->value)
		(*token)->value = exit_status;
	else
	{
		temp = (*token)->value;
		(*token)->value = ft_strjoin((*token)->value, exit_status);
		free(temp);
		free(exit_status);
	}
	*i += 2;
}
