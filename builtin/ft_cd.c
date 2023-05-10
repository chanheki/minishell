#include "../include/minishell.h"

/*
 * Description: *path 값에 따라 현재 작업 디렉토리를 변경한다.
 * Param.  #1 : 변경할 디렉토리 경로
 * Return     : 성공 시 0, 실패 시 1
 */
int	ft_cd(char **path)
{
	if (!(*path) || !path || ft_strcmp(*path, "~"))
		return (move_to_home());
	else
		return (move_to_dir(*path));
	return (0);
}
